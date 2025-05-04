CREATE OR REPLACE FUNCTION register_assistant(
    person_name TEXT,
    person_username TEXT,
    person_password TEXT,
    person_mail TEXT,

    contract_salary INT

) RETURNS INT AS $$

DECLARE
    new_person_id INT;

BEGIN

    INSERT INTO person (name, username, password, mail)
    VALUES (person_name, person_username, person_password, person_mail)
    RETURNING id INTO new_person_id;

    INSERT INTO employee_contract (contract_salary, person_id)
    VALUES (contract_salary, new_person_id);

    INSERT INTO assistant (employee_contract_person_id)
    VALUES (new_person_id);

    RETURN new_person_id;

END;
$$ LANGUAGE plpgsql;

SELECT register_assistant(%s, %s, %s, %s, %s);