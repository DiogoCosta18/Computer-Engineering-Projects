from flask import Flask, jsonify
from flask_jwt_extended import JWTManager, verify_jwt_in_request, get_jwt
from flask_bcrypt import Bcrypt
from psycopg2 import connect

from logging import getLogger
from functools import wraps
from os import getcwd, path

app = Flask(__name__)
bcrypt = Bcrypt(app)
app.config['JWT_SECRET_KEY'] = 'balls'

jwt = JWTManager(app)

logger = getLogger('logger')

StatusCodes = {
    'success': 200,
    'api_error': 400,
    'internal_error': 500
}

def db_connection():
    db = connect(
        user='zero_getter',
        password='1234',
        host='localhost',
        port='5432',
        database='we_are_getting_zero'
    )

    return db


def read_sql_file(file):

    base_path = getcwd()
    sql_file_path = path.join(base_path, 'src', 'queries', file)

    with open(sql_file_path, 'r') as file:
        sql = file.read()
    return sql


def check_payload(attributes, payload):

    for attribute in attributes:

        if attribute not in payload:
            response = {'status': StatusCodes['api_error'], 'results': f'{attribute} value not in payload'}
            return jsonify(response)
        
    return None

def roles_required(roles):
    def decorator(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            verify_jwt_in_request()
            claims = get_jwt()
            identity = claims.get('sub')
            if not identity or identity.get('role') not in roles:
                return jsonify(msg="Access denied"), 403
            return fn(*args, **kwargs)
        return wrapper
    return decorator