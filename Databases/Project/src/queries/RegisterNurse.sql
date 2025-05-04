CREATE OR REPLACE FUNCTION register_nurse(
    person_name TEXT,
    person_username TEXT,
    person_password TEXT,
    person_mail TEXT,

    contract_salary INT,

    responsible_for INT[]

) RETURNS INT AS $$

DECLARE
    new_person_id INT;
    nurse_id INT;

BEGIN

    INSERT INTO person (name, username, password, mail)
    VALUES (person_name, person_username, person_password, person_mail)
    RETURNING id INTO new_person_id;

    INSERT INTO employee_contract (contract_salary, person_id)
    VALUES (contract_salary, new_person_id);

    INSERT INTO nurse (employee_contract_person_id)
    VALUES (new_person_id);

    FOREACH nurse_id IN ARRAY responsible_for
    LOOP
        INSERT INTO nurse_nurse (nurse_employee_contract_person_id, nurse_employee_contract_person_id1)
        VALUES (nurse_id, new_person_id);
    END LOOP;

    RETURN new_person_id;

END;
$$ LANGUAGE plpgsql;

SELECT register_nurse(%s, %s, %s, %s, %s, %s);