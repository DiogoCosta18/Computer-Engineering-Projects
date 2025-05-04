CREATE OR REPLACE FUNCTION register_doctor(
    person_name TEXT,
    person_username TEXT,
    person_password TEXT,
    person_mail TEXT,

    contract_salary INT,

    doctor_specializations TEXT[]

) RETURNS INT AS $$

DECLARE
    new_person_id INT;
    spec TEXT;

BEGIN

    INSERT INTO person (name, username, password, mail)
    VALUES (person_name, person_username, person_password, person_mail)
    RETURNING id INTO new_person_id;

    INSERT INTO employee_contract (contract_salary, person_id)
    VALUES (contract_salary, new_person_id);

    INSERT INTO doctor (employee_contract_person_id)
    VALUES (new_person_id);

    FOREACH spec IN ARRAY doctor_specializations
    LOOP
        INSERT INTO doctor_specialization (doctor_employee_contract_person_id, specialization_name)
        VALUES (new_person_id, spec);
    END LOOP;

    RETURN new_person_id;

END;
$$ LANGUAGE plpgsql;

SELECT register_doctor(%s, %s, %s, %s, %s, %s);