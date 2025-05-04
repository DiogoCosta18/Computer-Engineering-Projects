DROP TRIGGER IF EXISTS before_hospitalization_insert ON hospitalization;

CREATE TRIGGER before_hospitalization_insert
BEFORE INSERT ON hospitalization
FOR EACH ROW
EXECUTE FUNCTION create_bill();

CREATE OR REPLACE FUNCTION post_surgery(
    startdate TIMESTAMP,
    doctor_employee_contract_person_id BIGINT,
    assistant_employee_contract_person_id BIGINT,
    patient_person_id BIGINT,
    nurses nurse_role_type[]
) 
RETURNS JSON
LANGUAGE plpgsql
AS $$

DECLARE
    hospitalization_id BIGINT;
    responsible_nurse BIGINT;
    new_surgery_id BIGINT;
    nurse_id BIGINT;
    nurse_record nurse_role_type;
    duration INTERVAL := INTERVAL '3 hours';
    status_code INT := 200;
    surgery_info JSON;
BEGIN
    BEGIN
        LOCK TABLE surgery IN SHARE MODE;

        IF NOT check_patient_availability(patient_person_id, startdate, duration) THEN
            RAISE EXCEPTION 'Patient is not available at this time';
        END IF;

        IF NOT check_doctor_availability(doctor_employee_contract_person_id, startdate, duration) THEN
            RAISE EXCEPTION 'Doctor is not available at this time';
        END IF;

        FOREACH nurse_record IN ARRAY nurses
        LOOP
            nurse_id := nurse_record.nurse_user_id;
            IF NOT check_nurse_availability(nurse_id, startdate, duration) THEN
                RAISE EXCEPTION 'Nurse is not available at this time';
            END IF;
        END LOOP;

        responsible_nurse := (SELECT nurse_user_id FROM unnest(nurses) ORDER BY random() LIMIT 1);

        INSERT INTO hospitalization (patient_person_id, startdate, responsible_nurse_id, assistant_employee_contract_person_id)
        VALUES (patient_person_id, startdate, responsible_nurse, assistant_employee_contract_person_id)
        RETURNING id INTO hospitalization_id;

        INSERT INTO surgery (startdate, doctor_employee_contract_person_id, assistant_employee_contract_person_id, patient_person_id, hospitalization_id)
        VALUES (startdate, doctor_employee_contract_person_id, assistant_employee_contract_person_id, patient_person_id, hospitalization_id)
        RETURNING id INTO new_surgery_id;

        FOREACH nurse_record IN ARRAY nurses LOOP
            INSERT INTO nurse_surgery_role (role, surgery_id, nurse_employee_contract_person_id)
            VALUES (nurse_record.role, new_surgery_id, nurse_record.nurse_user_id);
        END LOOP;

        surgery_info := json_build_object(
            'results', json_build_object(
                'date', startdate,
                'doctor_id', doctor_employee_contract_person_id,
                'hospitalization_id', hospitalization_id,
                'patient_id', patient_person_id,
                'surgery_id', new_surgery_id
            ),
            'status', status_code
        );
    END;

    RETURN surgery_info;
END;
$$;

SELECT post_surgery(
    %s,
    %s,
    %s,
    %s,
    %s::nurse_role_type[]
);
