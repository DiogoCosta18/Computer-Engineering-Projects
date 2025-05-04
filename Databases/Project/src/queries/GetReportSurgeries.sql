SELECT TO_CHAR(c.startdate, 'Month') AS month, p.name AS doctor, COUNT(*) AS surgery_count
FROM surgery c
JOIN person p ON c.doctor_employee_contract_person_id = p.id
WHERE c.startdate >= date %s - interval '1 year'
GROUP BY month, doctor
ORDER BY doctor, month;