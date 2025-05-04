SELECT p.id, p.validity, m.quantity, m.frequency, m.medicine_id, c.name
FROM prescription p
LEFT JOIN prescription_appointment k ON p.id = k.prescription_id
LEFT JOIN appointment a ON k.appointment_id = a.id
LEFT JOIN posology m ON p.id = m.prescription_id
LEFT JOIN medicine c ON m.medicine_id = c.id
LEFT JOIN prescription_hospitalization g ON p.id = g.prescription_id
LEFT JOIN hospitalization t ON g.hospitalization_id = t.id
WHERE (a.patient_person_id = %s OR t.patient_person_id = %s)
    AND (k.appointment_id IS NOT NULL OR g.hospitalization_id IS NOT NULL);