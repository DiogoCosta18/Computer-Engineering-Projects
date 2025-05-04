import flask
import psycopg2

import datetime

from utilities import *

@app.route('/dbproj/appointment/', methods=['POST'])
@roles_required(['patient'])
def post_appointment():
    logger.info('POST APPOINTMENT')

    payload = flask.request.get_json()

    logger.debug(f'POST /appointment/ - payload: {payload}')

    required_fields = ['startdate', 'doctor_employee_contract_person_id', 'assistant_employee_contract_person_id', 'nurse_employee_contract_person_id']
    invalid_appointment_payload = check_payload(required_fields, payload)

    if invalid_appointment_payload:
        return invalid_appointment_payload
    elif not payload['nurse_employee_contract_person_id']:
        response = {'status': StatusCodes['internal_error'], 'errors': 'The appointment needs to have at least one nurse'}
        return response
    else:
        startdate = payload['startdate']
        doctor_id = payload['doctor_employee_contract_person_id']
        assistant_id = payload['assistant_employee_contract_person_id']
        nurse_ids = payload['nurse_employee_contract_person_id']
    
    verify_jwt_in_request()
    claims = get_jwt()
    identity = claims.get('sub')
    if not identity:
        return jsonify({'status': StatusCodes['internal_error'], 'errors': "No token sent with request"})

    conn = db_connection()
    cur = conn.cursor()

    try:
        cur.execute(read_sql_file('PostCreateAppointment.sql'), (startdate, doctor_id, assistant_id, identity.get('user_id'), nurse_ids))

        new_appointment_id = cur.fetchone()[0]

        conn.commit()
        response = {'status': StatusCodes['success'], 'results': new_appointment_id}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/appointment/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}
        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)


@app.route('/dbproj/bills/<bill_id>', methods=['POST'])
@roles_required(['patient'])
def execute_payment(bill_id):
    logger.info(f'POST /bills/{bill_id}')

    payload = flask.request.get_json()

    logger.debug(f'POST /bills/{bill_id} - payload: {payload}')

    verify_jwt_in_request()
    claims = get_jwt()
    identity = claims.get('sub')
    if not identity:
        return jsonify(msg="No token sent with request"), 403

    invalid_payment_payload = check_payload(['amount'], payload)

    if invalid_payment_payload:
        return invalid_payment_payload
    else:
        current_date = datetime.datetime.now()
        postgres_date = current_date.strftime('%Y-%m-%d')
        appointment_values = (identity.get('user_id'), postgres_date,bill_id, payload['amount'])

    conn = db_connection()
    cur = conn.cursor()

    try:
        cur.execute(read_sql_file('PostExecutePayment.sql'), appointment_values)
        remaining_amount = cur.fetchone()[0]

        conn.commit()
        response = {'status': StatusCodes['success'], 'results': remaining_amount}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/bills/{bill_id} - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)

@app.route('/dbproj/surgery/<hospitalization_id>', methods=['POST'])
@roles_required(['assistant'])
def post_surgery_with_hospitalization(hospitalization_id):
    logger.info('POST SURGERY WITH HOSPITALIZATION')

    payload = flask.request.get_json()

    logger.debug(f'POST /surgery/ - payload: {payload}')

    invalid_appointment_payload = check_payload(['startdate', 'doctor_employee_contract_person_id', 'assistant_employee_contract_person_id', 'patient_person_id', 'nurses'], payload)
    
    if invalid_appointment_payload:
        return jsonify(invalid_appointment_payload)

    nurses = [(nurse['nurse_user_id'], nurse['role']) for nurse in payload['nurses']]
    appointment_values = (payload['startdate'], payload['doctor_employee_contract_person_id'], payload['assistant_employee_contract_person_id'], payload['patient_person_id'], nurses, hospitalization_id)

    conn = db_connection()
    cur = conn.cursor()

    try:
        sql = read_sql_file('PostScheduleSurgeryWithHospitalization.sql')
        cur.execute(sql, appointment_values)

        result = cur.fetchone()[0]

        conn.commit()

        status_code = result['status']
        if status_code == 200:
            return jsonify(result)
        else:
            response = {'status': StatusCodes['internal_error'] , 'errors': result['errors']}
            return jsonify(response)

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/surgery/<hospitalization_id> - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}
        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return jsonify(response)

@app.route('/dbproj/surgery/', methods=['POST'])
@roles_required(['assistant'])
def post_surgery():
    logger.info('POST SURGERY')

    payload = flask.request.get_json()

    logger.debug(f'POST /surgery/ - payload: {payload}')

    invalid_appointment_payload = check_payload(['startdate', 'doctor_employee_contract_person_id', 'assistant_employee_contract_person_id', 'patient_person_id', 'nurses'], payload)

    nurses = [(nurse['nurse_user_id'], nurse['role']) for nurse in payload['nurses']]

    if invalid_appointment_payload:
        return invalid_appointment_payload
    else:
        appointment_values = (payload['startdate'], payload['doctor_employee_contract_person_id'], payload['assistant_employee_contract_person_id'], payload['patient_person_id'], nurses)

    conn = db_connection()
    cur = conn.cursor()
    try:
        sql = read_sql_file('PostScheduleSurgery.sql')
        cur.execute(sql, appointment_values)

        result = cur.fetchone()[0]

        conn.commit()

        if 'status' in result:
            status_code = result['status']
            if status_code == 200:
                return jsonify(result)
            else:
                response = {'status': StatusCodes['internal_error'], 'errors': result.get('errors', 'Unknown error')}
                return jsonify(response)
        else:
            response = {'status': StatusCodes['internal_error'], 'errors': 'Status key not found in result'}
            return jsonify(response)

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/surgery/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)


@app.route('/dbproj/prescription/', methods=['POST'])
@roles_required(['doctor'])
def post_prescription():
    logger.info('POST PRESCRIPTION')

    payload = flask.request.get_json()
    logger.debug(f'POST /prescription/ - payload: {payload}')

    invalid_prescription_payload = check_payload(['type', 'validity', 'posology_information', 'event_id'], payload)
    if invalid_prescription_payload:
        return invalid_prescription_payload

    posology_info = payload['posology_information']
    for info in posology_info:
        if not all(field in info for field in ['medicine_name', 'posology_dose', 'posology_quantity']):
            return {'status': StatusCodes['bad_request'], 'errors': 'Invalid posology information format'}

    prescription_values = (
        payload['type'],
        payload['validity'],
        [tuple(info.values()) for info in posology_info],
        payload['event_id']
    )

    conn = db_connection()
    cur = conn.cursor()

    try:
        logger.debug(f'Parameters: {prescription_values}')

        cur.execute(read_sql_file('PostAddPrescription.sql'), prescription_values)
        new_prescription_id = cur.fetchone()[0]

        conn.commit()
        response = {'status': StatusCodes['success'], 'results': new_prescription_id}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/prescription/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}
        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)