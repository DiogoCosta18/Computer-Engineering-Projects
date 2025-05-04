LOCK TABLE bill IN SHARE MODE;

WITH patient_appointments AS (

SELECT appointment.patient_person_id,
   SUM(payment.partial_or_total_amount) AS paid_amount,
   'appointment' AS procedure_type,
   appointment.id AS procedure_id,
   appointment.doctor_employee_contract_person_id AS doctor_id,
   appointment.startdate AS procedure_date

FROM appointment, bill, payment
WHERE appointment.bill_id = bill.id AND bill.id = payment.bill_id AND
  EXTRACT(MONTH FROM payment.payment_date) = EXTRACT(MONTH FROM CURRENT_DATE) AND EXTRACT(YEAR FROM payment.payment_date) = EXTRACT(YEAR FROM CURRENT_DATE)
GROUP BY appointment.patient_person_id, appointment.id

), patient_surgeries AS (

SELECT hospitalization.patient_person_id, 
   SUM(payment.partial_or_total_amount) AS paid_amount,
   'surgery' AS procedure_type,
   surgery.id AS procedure_id,
   surgery.doctor_employee_contract_person_id AS doctor_id,
   surgery.startdate AS procedure_date

FROM surgery, hospitalization, bill, payment
WHERE surgery.hospitalization_id = hospitalization.id AND hospitalization.bill_id = bill.id AND bill.id = payment.bill_id AND
  EXTRACT(MONTH FROM payment.payment_date) = EXTRACT(MONTH FROM CURRENT_DATE) AND EXTRACT(YEAR FROM payment.payment_date) = EXTRACT(YEAR FROM CURRENT_DATE)
GROUP BY hospitalization.patient_person_id, hospitalization_id, surgery.id
  
), all_bills AS (

SELECT patient_person_id, paid_amount, procedure_type, procedure_id, doctor_id, procedure_date 
FROM patient_appointments
UNION ALL
SELECT patient_person_id, paid_amount, procedure_type, procedure_id, doctor_id, procedure_date 
FROM patient_surgeries

), total_spent AS (

SELECT patient_person_id, SUM(paid_amount) AS total_amount_spent
FROM all_bills
GROUP BY patient_person_id

), ranked_patients AS (

SELECT patient_person_id, total_amount_spent, ROW_NUMBER() OVER (ORDER BY total_amount_spent DESC) AS rank
FROM total_spent

)

SELECT ranked_patients.patient_person_id, person.name, ranked_patients.total_amount_spent, all_bills.procedure_type, all_bills.procedure_id, all_bills.doctor_id, all_bills.procedure_date
FROM ranked_patients, person, all_bills, patient
WHERE ranked_patients.patient_person_id = patient.person_id AND patient.person_id = person.id AND ranked_patients.patient_person_id = all_bills.patient_person_id AND ranked_patients.rank <= 3
ORDER BY ranked_patients.rank;