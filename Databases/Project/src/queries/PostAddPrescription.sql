CREATE OR REPLACE FUNCTION create_prescription(
  p_type TEXT,
  p_validity DATE,
  p_medicines posology_information[], 
  p_event_id BIGINT
)

RETURNS INT LANGUAGE plpgsql AS $$
DECLARE
  variable_prescription_id INT;
BEGIN

  INSERT INTO prescription (startdate, validity)
  VALUES (current_date, p_validity)
  RETURNING id INTO variable_prescription_id;

  IF p_type = 'appointment' THEN
    INSERT INTO prescription_appointment (prescription_id, appointment_id)
    VALUES (variable_prescription_id, p_event_id);
  ELSIF p_type = 'hospitalization' THEN
    INSERT INTO prescription_hospitalization (prescription_id, hospitalization_id)
    VALUES (variable_prescription_id, p_event_id);
  END IF;

  INSERT INTO posology (quantity, frequency, medicine_id, prescription_id)
  SELECT pm.posology_dose, pm.posology_quantity, m.id, variable_prescription_id
  FROM unnest(p_medicines) pm
  JOIN medicine m ON m.name = pm.medicine_name;

  RETURN variable_prescription_id;
END;
$$;

SELECT create_prescription(
%s,
%s,
%s::posology_information[],
%s
);