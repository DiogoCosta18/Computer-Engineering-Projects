import flask
import flask_jwt_extended
import psycopg2

from utilities import *

@app.route('/dbproj/register/<role>', methods=['POST'])
def register_user(role):
    logger.info(f'POST /register/{role}')

    payload = flask.request.get_json()

    logger.debug(f'POST /register/{role} - payload: {payload}')

    invalid_user_payload = check_payload(['name', 'username', 'password', 'mail'], payload)
    if invalid_user_payload:
        return invalid_user_payload
    else:
        hashed_password = bcrypt.generate_password_hash(payload['password']).decode('utf-8')
        person_values = (payload['name'], payload['username'], hashed_password, payload['mail'])

    #check and define attributes for a patient
    match role:
        case "patient":
            register_user_query = read_sql_file('RegisterPatient.sql')
        
        case "doctor":
            invalid_doctor_payload = check_payload(['contract_salary', 'doctor_specializations'], payload)
            if invalid_doctor_payload:
                return invalid_doctor_payload
            else:
                person_values = (payload['name'], payload['username'], hashed_password, payload['mail'], payload['contract_salary'], payload['doctor_specializations'])
                register_user_query = read_sql_file('RegisterDoctor.sql')
        
        case "nurse":
            invalid_nurse_payload = check_payload(['responsible_for'], payload)
            if invalid_nurse_payload:
                return invalid_nurse_payload
            else:
                person_values = (payload['name'], payload['username'], hashed_password, payload['mail'], payload['contract_salary'], payload['responsible_for'])
                register_user_query = read_sql_file('RegisterNurse.sql')

        case "assistant":
            invalid_assistant_payload = check_payload(['contract_salary'], payload)
            if invalid_assistant_payload:
                return invalid_assistant_payload
            else:
                person_values = (payload['name'], payload['username'], hashed_password, payload['mail'], payload['contract_salary'])
                register_user_query = read_sql_file('RegisterAssistant.sql')
        
        case _:
            response = {
                'status': StatusCodes['api_error'],
                'results': 'Role doesnt exist'
            }
            return flask.jsonify(response)


    conn = db_connection()
    cur = conn.cursor()
    
    try:
        cur.execute(register_user_query, person_values)
        new_person_id = cur.fetchone()[0]

        conn.commit()
        response = {
            'status': StatusCodes['success'],
            'results': new_person_id
        }

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'POST /dbproj/register/{role} - error: {error}')
        response = {
            'status': StatusCodes['internal_error'],
            'errors': str(error)
        }

        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)


@app.route('/dbproj/user', methods=['PUT'])
def login_user():
    logger.info('PUT /user')

    payload = flask.request.get_json()

    logger.debug(f'POST /user - payload: {payload}')

    invalid_login_payload = check_payload(['username', 'password'], payload)
    if invalid_login_payload:
        return invalid_login_payload
    
    conn = db_connection()
    cur = conn.cursor()

    login_values = (payload['username'],)

    try:
        cur.execute(read_sql_file('LoginUser.sql'), login_values)

        user = cur.fetchone()

        if user is None:
            response = {
                'status': StatusCodes['internal_error'],
                'errors': f'User {payload['username']} does not exit'
            }
            return flask.jsonify(response)
        
        user_id, hashed_password, user_role = user

        if not bcrypt.check_password_hash(hashed_password, payload['password']):
            response = {
                'status': 'error',
                'errors': 'Invalid username or password'
            }
            return jsonify(response)

        access_token = flask_jwt_extended.create_access_token(identity={'role': user_role, 'user_id': user_id})

        conn.commit()
        response = {
            'status': StatusCodes['success'],
            'results': access_token
        }

    except (Exception, psycopg2.DatabaseError) as error:
        logger.error(f'PUT /dbproj/user - error: {error}')
        response = {
            'status': StatusCodes['internal_error'],
            'errors': str(error)
        }

        conn.rollback()

    finally:
        if conn is not None:
            conn.close()

    return flask.jsonify(response)