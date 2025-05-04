SELECT u.id, u.password, 
                        CASE
                            WHEN p.person_id IS NOT NULL THEN 'patient'
                            WHEN d.employee_contract_person_id IS NOT NULL THEN 'doctor'
                            WHEN n.employee_contract_person_id IS NOT NULL THEN 'nurse'
                            WHEN a.employee_contract_person_id IS NOT NULL THEN 'assistant'
                            ELSE 'unknown'
                        END AS role

FROM person u
LEFT JOIN patient p ON u.id = p.person_id
LEFT JOIN employee_contract e ON u.id = e.person_id
LEFT JOIN doctor d ON e.person_id = d.employee_contract_person_id
LEFT JOIN nurse n ON e.person_id = n.employee_contract_person_id
LEFT JOIN assistant a ON e.person_id = a.employee_contract_person_id
WHERE u.username = %s;