CREATE OR REPLACE FUNCTION execute_payment(
    token_user_id INT,
    payment_date_value DATE,
    bill_id_value INT,
    payment_amount DOUBLE PRECISION

) RETURNS DOUBLE PRECISION AS $$

DECLARE
    total_amount DOUBLE PRECISION;
    remaining_amount DOUBLE PRECISION;
    patient_id INT;

BEGIN

    IF payment_amount <= 0 THEN
        RAISE EXCEPTION 'ERROR: amount needs to be a positive value';
    END IF;

    SELECT bill.amount, (bill.amount - COALESCE(SUM(payment.partial_or_total_amount), 0)), patient.person_id
    INTO total_amount, remaining_amount, patient_id
    FROM bill
    LEFT JOIN payment ON bill.id = payment.bill_id
    JOIN patient ON bill.patient_person_id = patient.person_id
    WHERE bill.id = bill_id_value
    GROUP BY bill.id, patient.person_id;

    IF token_user_id != patient_id THEN
        RAISE EXCEPTION 'ERROR: You cant pay another patients debts';
    END IF;

    IF remaining_amount < payment_amount THEN
        RAISE EXCEPTION 'ERROR: Payment amount exceeds the amount left to pay. Would you like to donate the extra to a childrens hospital fund?';
    ELSE

        INSERT INTO payment(payment_date, partial_or_total_amount, bill_id)
        VALUES (payment_date_value, payment_amount, bill_id_value);
    END IF;

    RETURN remaining_amount - payment_amount;

END;
$$ LANGUAGE plpgsql;

SELECT execute_payment(%s, %s, %s, %s);