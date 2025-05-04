CREATE TABLE patient (
	person_id BIGINT,
	PRIMARY KEY(person_id)
);

CREATE TABLE employee_contract (
	contract_salary INTEGER NOT NULL,
	person_id	 BIGINT,
	PRIMARY KEY(person_id)
);

CREATE TABLE hospitalization (
	id					 BIGSERIAL,
	startdate				 TIMESTAMP NOT NULL,
	responsible_nurse_id			 BIGINT NOT NULL,
	bill_id				 BIGINT NOT NULL,
	assistant_employee_contract_person_id BIGINT NOT NULL,
	patient_person_id			 BIGINT NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE surgery (
	id					 BIGSERIAL,
	startdate				 TIMESTAMP NOT NULL,
	doctor_employee_contract_person_id	 BIGINT NOT NULL,
	assistant_employee_contract_person_id BIGINT NOT NULL,
	patient_person_id			 BIGINT NOT NULL,
	hospitalization_id			 BIGINT NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE appointment (
	id					 BIGSERIAL,
	startdate				 TIMESTAMP NOT NULL,
	bill_id				 BIGINT NOT NULL,
	doctor_employee_contract_person_id	 BIGINT NOT NULL,
	assistant_employee_contract_person_id BIGINT NOT NULL,
	patient_person_id			 BIGINT NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE doctor (
	employee_contract_person_id BIGINT,
	PRIMARY KEY(employee_contract_person_id)
);

CREATE TABLE nurse (
	employee_contract_person_id BIGINT,
	PRIMARY KEY(employee_contract_person_id)
);

CREATE TABLE assistant (
	employee_contract_person_id BIGINT,
	PRIMARY KEY(employee_contract_person_id)
);

CREATE TABLE specialization (
	name VARCHAR(512),
	PRIMARY KEY(name)
);

CREATE TABLE bill (
	id		 BIGSERIAL,
	amount		 DOUBLE PRECISION NOT NULL,
	status		 BOOL NOT NULL,
	patient_person_id BIGINT NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE payment (
	id			 BIGSERIAL,
	payment_date		 DATE NOT NULL,
	partial_or_total_amount DOUBLE PRECISION NOT NULL,
	bill_id		 BIGINT NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE prescription (
	id	 BIGSERIAL,
	startdate DATE NOT NULL,
	validity	 DATE NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE medicine (
	id	 BIGSERIAL,
	name VARCHAR(512) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE side_effect (
	occurrences INTEGER,
	severity	 INTEGER
);

CREATE TABLE posology (
	quantity	 INTEGER NOT NULL,
	frequency	 BIGINT NOT NULL,
	medicine_id	 BIGINT,
	prescription_id BIGINT,
	PRIMARY KEY(medicine_id,prescription_id)
);

CREATE TABLE person (
	id	 BIGSERIAL,
	name	 VARCHAR(512) NOT NULL,
	username VARCHAR(512) NOT NULL,
	password VARCHAR(512) NOT NULL,
	mail	 VARCHAR(512) NOT NULL,
	PRIMARY KEY(id)
);

CREATE TABLE nurse_surgery_role (
	role				 VARCHAR(512) NOT NULL,
	nurse_employee_contract_person_id BIGINT,
	surgery_id			 BIGINT,
	PRIMARY KEY(nurse_employee_contract_person_id,surgery_id)
);

CREATE TABLE nurse_appointment_role (
	role				 VARCHAR(512) NOT NULL,
	nurse_employee_contract_person_id BIGINT,
	appointment_id			 BIGINT,
	PRIMARY KEY(nurse_employee_contract_person_id,appointment_id)
);

CREATE TABLE nurse_nurse (
	nurse_employee_contract_person_id	 BIGINT,
	nurse_employee_contract_person_id1 BIGINT NOT NULL,
	PRIMARY KEY(nurse_employee_contract_person_id)
);

CREATE TABLE nurse_hospitalization (
	nurse_employee_contract_person_id BIGINT,
	hospitalization_id		 BIGINT,
	PRIMARY KEY(nurse_employee_contract_person_id,hospitalization_id)
);

CREATE TABLE doctor_hospitalization (
	doctor_employee_contract_person_id BIGINT NOT NULL,
	hospitalization_id		 BIGINT,
	PRIMARY KEY(hospitalization_id)
);

CREATE TABLE prescription_appointment (
	prescription_id BIGINT,
	appointment_id	 BIGINT NOT NULL,
	PRIMARY KEY(prescription_id)
);

CREATE TABLE prescription_hospitalization (
	prescription_id	 BIGINT,
	hospitalization_id BIGINT NOT NULL,
	PRIMARY KEY(prescription_id)
);

CREATE TABLE medicine_side_effect (
	medicine_id BIGINT,
	PRIMARY KEY(medicine_id)
);

CREATE TABLE specialization_specialization (
	specialization_name	 VARCHAR(512),
	specialization_name1 VARCHAR(512) NOT NULL,
	PRIMARY KEY(specialization_name)
);

CREATE TABLE doctor_specialization (
	doctor_employee_contract_person_id BIGINT,
	specialization_name		 VARCHAR(512),
	PRIMARY KEY(doctor_employee_contract_person_id,specialization_name)
);

ALTER TABLE patient ADD CONSTRAINT patient_fk1 FOREIGN KEY (person_id) REFERENCES person(id);
ALTER TABLE employee_contract ADD CONSTRAINT employee_contract_fk1 FOREIGN KEY (person_id) REFERENCES person(id);
ALTER TABLE hospitalization ADD CONSTRAINT hospitalization_fk1 FOREIGN KEY (bill_id) REFERENCES bill(id);
ALTER TABLE hospitalization ADD CONSTRAINT hospitalization_fk2 FOREIGN KEY (assistant_employee_contract_person_id) REFERENCES assistant(employee_contract_person_id);
ALTER TABLE hospitalization ADD CONSTRAINT hospitalization_fk3 FOREIGN KEY (patient_person_id) REFERENCES patient(person_id);
ALTER TABLE surgery ADD CONSTRAINT surgery_fk1 FOREIGN KEY (doctor_employee_contract_person_id) REFERENCES doctor(employee_contract_person_id);
ALTER TABLE surgery ADD CONSTRAINT surgery_fk2 FOREIGN KEY (assistant_employee_contract_person_id) REFERENCES assistant(employee_contract_person_id);
ALTER TABLE surgery ADD CONSTRAINT surgery_fk3 FOREIGN KEY (patient_person_id) REFERENCES patient(person_id);
ALTER TABLE surgery ADD CONSTRAINT surgery_fk4 FOREIGN KEY (hospitalization_id) REFERENCES hospitalization(id);
ALTER TABLE appointment ADD UNIQUE (bill_id);
ALTER TABLE appointment ADD CONSTRAINT appointment_fk1 FOREIGN KEY (bill_id) REFERENCES bill(id);
ALTER TABLE appointment ADD CONSTRAINT appointment_fk2 FOREIGN KEY (doctor_employee_contract_person_id) REFERENCES doctor(employee_contract_person_id);
ALTER TABLE appointment ADD CONSTRAINT appointment_fk3 FOREIGN KEY (assistant_employee_contract_person_id) REFERENCES assistant(employee_contract_person_id);
ALTER TABLE appointment ADD CONSTRAINT appointment_fk4 FOREIGN KEY (patient_person_id) REFERENCES patient(person_id);
ALTER TABLE doctor ADD CONSTRAINT doctor_fk1 FOREIGN KEY (employee_contract_person_id) REFERENCES employee_contract(person_id);
ALTER TABLE nurse ADD CONSTRAINT nurse_fk1 FOREIGN KEY (employee_contract_person_id) REFERENCES employee_contract(person_id);
ALTER TABLE assistant ADD CONSTRAINT assistant_fk1 FOREIGN KEY (employee_contract_person_id) REFERENCES employee_contract(person_id);
ALTER TABLE bill ADD CONSTRAINT bill_fk1 FOREIGN KEY (patient_person_id) REFERENCES patient(person_id);
ALTER TABLE payment ADD CONSTRAINT payment_fk1 FOREIGN KEY (bill_id) REFERENCES bill(id);
ALTER TABLE posology ADD CONSTRAINT posology_fk1 FOREIGN KEY (medicine_id) REFERENCES medicine(id);
ALTER TABLE posology ADD CONSTRAINT posology_fk2 FOREIGN KEY (prescription_id) REFERENCES prescription(id);
ALTER TABLE person ADD UNIQUE (username, mail);
ALTER TABLE nurse_surgery_role ADD CONSTRAINT nurse_surgery_role_fk1 FOREIGN KEY (nurse_employee_contract_person_id) REFERENCES nurse(employee_contract_person_id);
ALTER TABLE nurse_surgery_role ADD CONSTRAINT nurse_surgery_role_fk2 FOREIGN KEY (surgery_id) REFERENCES surgery(id);
ALTER TABLE nurse_appointment_role ADD CONSTRAINT nurse_appointment_role_fk1 FOREIGN KEY (nurse_employee_contract_person_id) REFERENCES nurse(employee_contract_person_id);
ALTER TABLE nurse_appointment_role ADD CONSTRAINT nurse_appointment_role_fk2 FOREIGN KEY (appointment_id) REFERENCES appointment(id);
ALTER TABLE nurse_nurse ADD CONSTRAINT nurse_nurse_fk1 FOREIGN KEY (nurse_employee_contract_person_id) REFERENCES nurse(employee_contract_person_id);
ALTER TABLE nurse_nurse ADD CONSTRAINT nurse_nurse_fk2 FOREIGN KEY (nurse_employee_contract_person_id1) REFERENCES nurse(employee_contract_person_id);
ALTER TABLE nurse_hospitalization ADD CONSTRAINT nurse_hospitalization_fk1 FOREIGN KEY (nurse_employee_contract_person_id) REFERENCES nurse(employee_contract_person_id);
ALTER TABLE nurse_hospitalization ADD CONSTRAINT nurse_hospitalization_fk2 FOREIGN KEY (hospitalization_id) REFERENCES hospitalization(id);
ALTER TABLE doctor_hospitalization ADD CONSTRAINT doctor_hospitalization_fk1 FOREIGN KEY (doctor_employee_contract_person_id) REFERENCES doctor(employee_contract_person_id);
ALTER TABLE doctor_hospitalization ADD CONSTRAINT doctor_hospitalization_fk2 FOREIGN KEY (hospitalization_id) REFERENCES hospitalization(id);
ALTER TABLE prescription_appointment ADD UNIQUE (appointment_id);
ALTER TABLE prescription_appointment ADD CONSTRAINT prescription_appointment_fk1 FOREIGN KEY (prescription_id) REFERENCES prescription(id);
ALTER TABLE prescription_appointment ADD CONSTRAINT prescription_appointment_fk2 FOREIGN KEY (appointment_id) REFERENCES appointment(id);
ALTER TABLE prescription_hospitalization ADD UNIQUE (hospitalization_id);
ALTER TABLE prescription_hospitalization ADD CONSTRAINT prescription_hospitalization_fk1 FOREIGN KEY (prescription_id) REFERENCES prescription(id);
ALTER TABLE prescription_hospitalization ADD CONSTRAINT prescription_hospitalization_fk2 FOREIGN KEY (hospitalization_id) REFERENCES hospitalization(id);
ALTER TABLE medicine_side_effect ADD CONSTRAINT medicine_side_effect_fk1 FOREIGN KEY (medicine_id) REFERENCES medicine(id);
ALTER TABLE specialization_specialization ADD CONSTRAINT specialization_specialization_fk1 FOREIGN KEY (specialization_name) REFERENCES specialization(name);
ALTER TABLE specialization_specialization ADD CONSTRAINT specialization_specialization_fk2 FOREIGN KEY (specialization_name1) REFERENCES specialization(name);
ALTER TABLE doctor_specialization ADD CONSTRAINT doctor_specialization_fk1 FOREIGN KEY (doctor_employee_contract_person_id) REFERENCES doctor(employee_contract_person_id);
ALTER TABLE doctor_specialization ADD CONSTRAINT doctor_specialization_fk2 FOREIGN KEY (specialization_name) REFERENCES specialization(name);

CREATE TYPE nurse_role_type AS (
    nurse_user_id BIGINT,
    role TEXT
);

CREATE TYPE posology_information AS (
    medicine_name TEXT,
    posology_dose INT,
    posology_quantity INT
);

CREATE OR REPLACE FUNCTION check_doctor_availability(
    doc_id BIGINT,
    start_time TIMESTAMP,
    duration INTERVAL
) RETURNS BOOLEAN AS $$

DECLARE
    end_time TIMESTAMP := start_time + duration;
    conflict_count INT;
BEGIN
    SELECT COUNT(*)
    INTO conflict_count
    FROM appointment
    WHERE doctor_employee_contract_person_id = doc_id
    AND (startdate, startdate + INTERVAL '1 hour') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    SELECT COUNT(*)
    INTO conflict_count
    FROM surgery
    WHERE doctor_employee_contract_person_id = doc_id
    AND (startdate, startdate + INTERVAL '3 hours') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_nurse_availability(
    nurse_id BIGINT,
    start_time TIMESTAMP,
    duration INTERVAL
) RETURNS BOOLEAN AS $$
DECLARE
    end_time TIMESTAMP := start_time + duration;
    conflict_count INT;
BEGIN
    SELECT COUNT(*)
    INTO conflict_count
    FROM appointment a
    JOIN nurse_appointment_role nar ON a.id = nar.appointment_id
    WHERE nar.nurse_employee_contract_person_id = nurse_id
    AND (a.startdate, a.startdate + INTERVAL '1 hour') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    SELECT COUNT(*)
    INTO conflict_count
    FROM surgery s
    JOIN nurse_surgery_role nsr ON s.id = nsr.surgery_id
    WHERE nsr.nurse_employee_contract_person_id = nurse_id
    AND (s.startdate, s.startdate + INTERVAL '3 hours') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_patient_availability(
    patient_id BIGINT,
    start_time TIMESTAMP,
    duration INTERVAL
) RETURNS BOOLEAN AS $$
DECLARE
    end_time TIMESTAMP := start_time + duration;
    conflict_count INT;
BEGIN
    SELECT COUNT(*)
    INTO conflict_count
    FROM appointment
    WHERE patient_person_id = patient_id
    AND (startdate, startdate + INTERVAL '1 hour') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    SELECT COUNT(*)
    INTO conflict_count
    FROM surgery
    WHERE patient_person_id = patient_id
    AND (startdate, startdate + INTERVAL '3 hours') OVERLAPS (start_time, end_time);

    IF conflict_count > 0 THEN
        RETURN FALSE;
    END IF;

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION create_bill()
RETURNS trigger
LANGUAGE plpgsql
AS $$
DECLARE
    new_bill_id BIGINT;
BEGIN

    LOCK TABLE bill IN EXCLUSIVE MODE;

    INSERT INTO bill (amount, status, patient_person_id)
    VALUES (1000, false, NEW.patient_person_id)
    RETURNING id INTO new_bill_id;

    NEW.bill_id = new_bill_id;
    
    RETURN NEW;
END;
$$;