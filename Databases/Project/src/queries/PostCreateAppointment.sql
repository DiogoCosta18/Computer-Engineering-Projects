DROP TRIGGER IF EXISTS before_appointment_insert ON appointment;

CREATE TRIGGER before_appointment_insert
BEFORE INSERT ON appointment
FOR EACH ROW
EXECUTE FUNCTION create_bill();

CREATE OR REPLACE FUNCTION create_appointment(
    new_start_timestamp TIMESTAMP,
    new_doctor_employee_contract_person_id BIGINT,
    new_assistant_employee_contract_person_id BIGINT,
    new_patient_person_id BIGINT,
    new_nurse_employee_contract_person_id BIGINT[]
) RETURNS BIGINT AS $$

DECLARE
    new_appointment_id BIGINT;
    nurse_id BIGINT;
    duration INTERVAL := INTERVAL '1 hour';

BEGIN
    LOCK TABLE appointment IN SHARE MODE;

    IF NOT check_patient_availability(new_patient_person_id, new_start_timestamp, duration) THEN
        RAISE EXCEPTION 'Patient is not available at this time';
    END IF;

    IF NOT check_doctor_availability(new_doctor_employee_contract_person_id, new_start_timestamp, duration) THEN
        RAISE EXCEPTION 'Doctor is not available at this time';
    END IF;

    FOREACH nurse_id IN ARRAY new_nurse_employee_contract_person_id
    LOOP
        IF NOT check_nurse_availability(nurse_id, new_start_timestamp, duration) THEN
            RAISE EXCEPTION 'Nurse is not available at this time';
        END IF;
    END LOOP;

    INSERT INTO appointment (startdate, doctor_employee_contract_person_id, assistant_employee_contract_person_id, patient_person_id)
    VALUES (new_start_timestamp, new_doctor_employee_contract_person_id, new_assistant_employee_contract_person_id, new_patient_person_id)
    RETURNING id INTO new_appointment_id;

    FOREACH nurse_id IN ARRAY new_nurse_employee_contract_person_id
    LOOP
        INSERT INTO nurse_appointment_role (role, appointment_id, nurse_employee_contract_person_id)
        VALUES ('role', new_appointment_id, nurse_id);
    END LOOP;

    RETURN new_appointment_id;
END;
$$ LANGUAGE plpgsql;

SELECT create_appointment(%s, %s, %s, %s, %s);