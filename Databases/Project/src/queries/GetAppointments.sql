SELECT appointment.id,
       appointment.startdate,
       appointment.doctor_employee_contract_person_id,
       person_doctor.name AS doctor_name,
       appointment.assistant_employee_contract_person_id,
       person_assistant.name AS assistant_name,
       nurse.employee_contract_person_id AS nurse_employee_contract_person_id,
       person_nurse.name AS nurse_name
FROM appointment
JOIN person AS person_patient ON appointment.patient_person_id = person_patient.id
JOIN person AS person_doctor ON appointment.doctor_employee_contract_person_id = person_doctor.id
LEFT JOIN person AS person_assistant ON appointment.assistant_employee_contract_person_id = person_assistant.id
LEFT JOIN nurse_appointment_role ON appointment.id = nurse_appointment_role.appointment_id
LEFT JOIN nurse ON nurse.employee_contract_person_id = nurse_appointment_role.nurse_employee_contract_person_id
LEFT JOIN person AS person_nurse ON nurse.employee_contract_person_id = person_nurse.id
WHERE person_patient.id = %s;