DROP FUNCTION IF EXISTS create_surgery(TIMESTAMP, BIGINT, BIGINT, BIGINT, nurse_role_type[], BIGINT);

CREATE OR REPLACE FUNCTION create_surgery(
    s_startdate TIMESTAMP,
    s_doctor_employee_contract_person_id BIGINT,
    s_assistant_employee_contract_person_id BIGINT,
    s_patient_person_id BIGINT,
    s_nurses nurse_role_type[],
    s_hospitalization_id BIGINT
) 
RETURNS JSON
LANGUAGE plpgsql AS $$
DECLARE
    new_surgery_id BIGINT;
    nurse_record nurse_role_type;
    nurse_id BIGINT;
    nurse_role TEXT;
    duration INTERVAL := INTERVAL '3 hours';
    status_code INT := 200;
    errors TEXT[] := '{}';
    result JSON := '{}'::JSON;
BEGIN
    BEGIN
        LOCK TABLE hospitalization IN SHARE MODE; 
        LOCK TABLE surgery IN SHARE MODE;

        IF NOT check_patient_availability(s_patient_person_id, s_startdate, duration) THEN
            RAISE EXCEPTION 'Patient is not available at this time';
        END IF;

        IF NOT check_doctor_availability(s_doctor_employee_contract_person_id, s_startdate, duration) THEN
            RAISE EXCEPTION 'Doctor is not available at this time';
        END IF;

        FOREACH nurse_record IN ARRAY s_nurses
        LOOP
            nurse_id := nurse_record.nurse_user_id;
            IF NOT check_nurse_availability(nurse_id, s_startdate, duration) THEN
                RAISE EXCEPTION 'Nurse is not available at this time';
            END IF;
        END LOOP;

        INSERT INTO surgery (startdate, doctor_employee_contract_person_id, assistant_employee_contract_person_id, patient_person_id, hospitalization_id)
        VALUES (s_startdate, s_doctor_employee_contract_person_id, s_assistant_employee_contract_person_id, s_patient_person_id, s_hospitalization_id)
        RETURNING id INTO new_surgery_id;

        FOREACH nurse_record IN ARRAY s_nurses
        LOOP
            nurse_id := nurse_record.nurse_user_id;
            nurse_role := nurse_record.role;
            INSERT INTO nurse_surgery_role (role, surgery_id, nurse_employee_contract_person_id)
            VALUES (nurse_role, new_surgery_id, nurse_id);
        END LOOP;

        result := json_build_object(
            'hospitalization_id', s_hospitalization_id,
            'surgery_id', new_surgery_id,
            'patient_id', s_patient_person_id,
            'doctor_id', s_doctor_employee_contract_person_id,
            'date', s_startdate
        );
    END;

    RETURN json_build_object(
        'status', status_code,
        'results', result
    );
END;
$$;

SELECT create_surgery(
    %s,
    %s,
    %s,
    %s,
    %s::nurse_role_type[],
    %s
);
