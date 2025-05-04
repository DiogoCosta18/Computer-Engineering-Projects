SELECT 
  SUM(bill.amount) AS amount_spent,
  COUNT(surgery) AS surgeries,
  COUNT(ph) AS prescriptions
FROM hospitalization
JOIN bill ON bill.id = hospitalization.bill_id
LEFT JOIN surgery ON surgery.hospitalization_id = hospitalization.id
LEFT JOIN prescription_hospitalization AS ph ON ph.hospitalization_id = hospitalization.id  
WHERE DATE(hospitalization.startdate) = %s;