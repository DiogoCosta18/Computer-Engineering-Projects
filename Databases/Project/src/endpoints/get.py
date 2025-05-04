import flask
import psycopg2
import datetime

from utilities import *

@app.route('/dbproj/report/', methods=['GET'])
@roles_required(['assistant'])
def get_report_surgeries():
    logger.info('GET REPORT SURGERIES')

    conn = db_connection()
    cur = conn.cursor()

    try:
        current_date = datetime.datetime.now()
        postgres_date = current_date.strftime('%Y-%m-%d')

        cur.execute(read_sql_file('GetReportSurgeries.sql'), (postgres_date,))
        rows = cur.fetchall()
        column_names = [desc[0] for desc in cur.description]

        logger.debug('GET REPORT SURGERIES')
        Results = []
        for row in rows:
            logger.debug(row)
            Results.append(dict(zip(column_names, row)))

        response = {'status': StatusCodes['success'], 'results': Results}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'GET /dbproj/report/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)


@app.route('/dbproj/appointment/<patient_user_id>', methods=['GET'])
@roles_required(['assistant', 'patient'])
def get_appointments(patient_user_id):
    logger.info('GET APPOINTMENT')

    verify_jwt_in_request()
    claims = get_jwt()
    identity = claims.get('sub')
    if not identity:
        return jsonify({'status': StatusCodes['internal_error'], 'errors': "No token sent with request"})
    
    
    if identity.get('role') == 'patient' and int(identity.get('user_id')) != int(patient_user_id):
        return jsonify({'status': StatusCodes['internal_error'], 'errors': "No permission to check another patients appointments"})

    conn = db_connection()
    cur = conn.cursor()

    try:
        cur.execute(read_sql_file('GetAppointments.sql'), (patient_user_id,))
        rows = cur.fetchall()

        column_names = [desc[0] for desc in cur.description]

        logger.debug('GET APPOINTMENT')
        appointment_map = {}
        
        for row in rows:
            logger.debug(row)
            appointment_id = row[column_names.index('id')]
            
            if appointment_id not in appointment_map:
                appointment_map[appointment_id] = {
                    'id': appointment_id,
                    'startdate': row[column_names.index('startdate')],
                    'doctor_employee_contract_person_id': row[column_names.index('doctor_employee_contract_person_id')],
                    'doctor_name': row[column_names.index('doctor_name')],
                    'assistant_employee_contract_person_id': row[column_names.index('assistant_employee_contract_person_id')],
                    'assistant_name': row[column_names.index('assistant_name')],
                    'nurses': []
                }
            
            nurse = {
                'nurse_employee_contract_person_id': row[column_names.index('nurse_employee_contract_person_id')],
                'nurse_name': row[column_names.index('nurse_name')]
            }
            appointment_map[appointment_id]['nurses'].append(nurse)
        
        Results = list(appointment_map.values())
        response = {'status': StatusCodes['success'], 'results': Results}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'GET /dbproj/appointment/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)



@app.route('/dbproj/prescriptions/<person_id>', methods=['GET'])
@roles_required(['assistant', 'doctor', 'nurse', 'patient'])
def get_prescriptions(person_id,):
    logger.info('GET PRESCRIPTIONS')

    verify_jwt_in_request()
    claims = get_jwt()
    identity = claims.get('sub')
    if not identity:
        return jsonify({'status': StatusCodes['internal_error'], 'errors': "No token sent with request"})
    
    
    if identity.get('role') == 'patient' and int(identity.get('user_id')) != int(person_id):
        return jsonify({'status': StatusCodes['internal_error'], 'errors': "No permission to check another patients appointments"})

    conn = db_connection()
    cur = conn.cursor()

    try:
        cur.execute(read_sql_file('GetPrescriptions.sql'), (person_id, person_id))
        rows = cur.fetchall()
        column_names = [desc[0] for desc in cur.description]

        logger.debug('GET PRESCRIPTIONS')
        Results = []
        for row in rows:
            logger.debug(row)
            Results.append(dict(zip(column_names, row)))  # Create a dictionary for each row

        response = {'status': StatusCodes['success'], 'results': Results}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'GET /dbproj/prescriptions/<person_id> - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)

@app.route('/dbproj/daily/<date>', methods=['GET'])
@roles_required(['assistant'])
def get_daily_hospitalization(date):
    logger.info('GET DAILY HOSPITALIZATIONS')

    conn = db_connection()
    cur = conn.cursor()

    try:
        cur.execute(read_sql_file('GetDailyHospitalization.sql'), (date,) )
        rows = cur.fetchall()
        column_names = [desc[0] for desc in cur.description]

        logger.debug('GET DAILY HOSPITALIZATIONS')
        Results = []
        for row in rows:
            logger.debug(row)
            Results.append(dict(zip(column_names, row)))

        response = {'status': StatusCodes['success'], 'results': Results}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'GET /dbproj/daily/<year-month-day> - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)


@app.route('/dbproj/top3/', methods=['GET'])
@roles_required(['assistant'])
def get_top3_patients():
    logger.info('GET TOP3 PATIENTS')

    conn = db_connection()
    cur = conn.cursor()

    try:
        sql = read_sql_file('GetTop3.sql')
        cur.execute(sql)
        rows = cur.fetchall()
        column_names = [desc[0] for desc in cur.description]

        logger.debug('GET TOP3 PATIENTS')
        results = []
        current_patient = None
        current_procedures = []
        
        for row in rows:
            row_dict = dict(zip(column_names, row))
            
            if row_dict['patient_person_id'] != current_patient:
                if current_patient is not None:
                    results.append({
                        'patient_name': current_patient_name,
                        'amount_spent': current_amount_spent,
                        'procedures': current_procedures
                    })
                current_patient = row_dict['patient_person_id']
                current_patient_name = row_dict['name']
                current_amount_spent = row_dict['total_amount_spent']
                current_procedures = []
            
            current_procedures.append({
                'id': row_dict['procedure_id'],
                'doctor_id': row_dict['doctor_id'],
                'date': row_dict['procedure_date']
            })

        if current_patient is not None:
            results.append({
                'patient_name': current_patient_name,
                'amount_spent': current_amount_spent,
                'procedures': current_procedures
            })

        response = {'status': StatusCodes['success'], 'results': results}

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'GET /dbproj/top3/ - error: {error}')
        response = {'status': StatusCodes['internal_error'], 'errors': str(error)}

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)