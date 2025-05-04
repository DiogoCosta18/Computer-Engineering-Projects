import gymnasium as gym
import numpy as np
import pygame

ENABLE_WIND = False #False
#ENABLE_WIND = True
WIND_POWER = 15.0
TURBULENCE_POWER = 0.0
GRAVITY = -10.0
RENDER_MODE = 'human' #'human'
RENDER_MODE = None #seleccione esta opção para não visualizar o ambiente (testes mais rápidos)
EPISODES = 1000

env = gym.make("LunarLander-v3", render_mode =RENDER_MODE, 
    continuous=True, gravity=GRAVITY, 
    enable_wind=ENABLE_WIND, wind_power=WIND_POWER, 
    turbulence_power=TURBULENCE_POWER)


def check_successful_landing(observation):
    x = observation[0]
    vy = observation[3]
    theta = observation[4]
    contact_left = observation[6]
    contact_right = observation[7]

    legs_touching = contact_left == 1 and contact_right == 1

    on_landing_pad = abs(x) <= 0.2

    stable_velocity = vy > -0.2
    stable_orientation = abs(theta) < np.deg2rad(20)
    stable = stable_velocity and stable_orientation
 
    if legs_touching and on_landing_pad and stable:
        print("✅ Aterragem bem sucedida!")
        return True

    print("⚠️ Aterragem falhada!")        
    return False
        
def simulate(steps=1000,seed=None, policy = None):    
    observation, _ = env.reset(seed=seed)
    for step in range(steps):
        action = policy(observation)

        observation, _, term, trunc, _ = env.step(action)

        if term or trunc:
            break

    success = check_successful_landing(observation)
    return step, success



#Perceptions
def is_tilted_left(observation):
    return observation[4] < -np.deg2rad(1)

def is_tilted_right(observation):
    return observation[4] > np.deg2rad(1)

def is_moving_left(observation):
    return observation[2] < 0

def is_moving_right(observation):
    return observation[2] > 0

def is_above_landing_zone(observation):
    return abs(observation[0]) < 0.2

def on_left_landing_zone(observation):
    return observation[0] < -0.2

def on_right_landing_zone(observation):
    return observation[0] > 0.2

def is_falling_fast(observation):
    return observation[3] < -0.4

def is_rotating_clockwise(observation):
    return observation[5] < 0

def is_rotating_counterclockwise(observation):
    return observation[5] > 0

def legs_are_touching(observation):
    return observation[6] == 1 and observation[7] == 1

def above_altitude_threshold(observation):
    return observation[1] > 0.57

# Modificação par a o vento com limiar
def is_tilted_left_wind(observation, d):
    return observation[4] > np.deg2rad(d)

def is_tilted_right_wind(observation, d):
    return observation[4] < -np.deg2rad(d)

#Actions
def thrust_main_engine(power=1.0):
    return [power, 0]

def thrust_side_engines(power=0):
    return [0, power]

def no_thrust():
    return [0, 0]


def reactive_agent(observation):
    # Extrai as percepções do ambiente
    x, y, vx, vy, theta, theta_dot, _, _ = observation

    # Separação de secções
    # Se está acima da zona de aterragem
    if is_above_landing_zone(observation):
        # Corrigir a inclinação + velocidade
        if (is_tilted_right_wind(observation, 1)) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(-0.51)[1]]
        if (is_tilted_left_wind(observation, 1)) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(0.51)[1]]
        # Corrigir a velocidade
        if is_falling_fast(observation):
            return thrust_main_engine(0.51)
        return no_thrust()
    
    # Se está á esquerda da zona de aterragem
    if on_left_landing_zone(observation):
        # Se está a mover-se para a esquerda
        if is_moving_left(observation):
            # Se estiver perto do chão aumentar motor central
            if is_tilted_left_wind(observation, -3) and (not above_altitude_threshold(observation)):
                return [ thrust_main_engine(0.7)[0], thrust_side_engines(0.7)[1]]
            if is_tilted_right_wind(observation, 12) and (not above_altitude_threshold(observation)):
                return [ thrust_main_engine(0.7)[0], thrust_side_engines(-0.6)[1]]
            # Se não estiver perto do chão, foco em virar
            if is_tilted_left_wind(observation, -3):
                return [ thrust_main_engine(0.51)[0], thrust_side_engines(0.7)[1]]
            if is_tilted_right_wind(observation, 12):
                return [ thrust_main_engine(0.51)[0], thrust_side_engines(-0.6)[1]]
            
        # Se não se está a mover para a esquerda
        # Virar para a direita se estiver demasiado virado para a esquerda
        if is_tilted_left_wind(observation, -1) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(0.6)[1]]
        if is_tilted_left_wind(observation, -1):
            return [ 0, thrust_side_engines(0.6)[1]]
            
        # Virar para a esquerda
        if is_tilted_right_wind(observation, 10 ) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(-0.6)[1]]
        if is_tilted_right_wind(observation, 10 ):
            return [ 0, thrust_side_engines(-0.6)[1]]
        
        return [thrust_main_engine(0.65)[0], thrust_side_engines(0.51)[1]]
    
    # Se está á direita da zona de aterragem
    if on_right_landing_zone(observation):
        # Se está a mover-se para a direita
        if is_moving_right(observation):   
            # Se estiver perto do chão aumentar motor central 
            if is_tilted_right_wind(observation, -3) and (not above_altitude_threshold(observation)):
                return [ thrust_main_engine(0.7)[0], thrust_side_engines(-0.7)[1]]
            if is_tilted_left_wind(observation, 12) and (not above_altitude_threshold(observation)):
                return [ thrust_main_engine(0.7)[0], thrust_side_engines(0.6)[1]]
            # Se não estiver perto do chão, foco em virar
            if is_tilted_right_wind(observation, -3):
                return [ thrust_main_engine(0.51)[0], thrust_side_engines(-0.7)[1]]
            if is_tilted_left_wind(observation, 12):
                return [ thrust_main_engine(0.51)[0], thrust_side_engines(0.6)[1]]
            
        # Se não se está a mover para a direita
        # Virar para a direita se estiver demasiado virado para a esquerda
        if is_tilted_left_wind(observation, 10 ) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(0.6)[1]]
        if is_tilted_left_wind(observation, 10 ):
            return [ 0, thrust_side_engines(0.6)[1]]
        
        # Virar para a esquerda
        if is_tilted_right_wind(observation, -1) and is_falling_fast(observation):
            return [ thrust_main_engine(0.51)[0], thrust_side_engines(-0.6)[1]]
        if is_tilted_right_wind(observation, -1):
            return [ 0, thrust_side_engines(-0.6)[1]]

        return [thrust_main_engine(0.65)[0], thrust_side_engines(-0.51)[1]]
    
    return no_thrust()
    
def keyboard_agent(observation):
    action = [0,0] 
    keys = pygame.key.get_pressed()
    
    print('observação:',observation)

    if keys[pygame.K_UP]:  
        action =+ np.array([1,0])
    if keys[pygame.K_LEFT]:  
        action =+ np.array( [0,-1])
    if keys[pygame.K_RIGHT]: 
        action =+ np.array([0,1])

    return action


success = 0.0
steps = 0.0
for i in range(EPISODES):
    st, su = simulate(steps=1000000, policy=reactive_agent)
    if su:
        steps += st
    success += su
        
    if su>0:
        print('Média de passos das aterragens bem sucedidas:', steps/(su*(i+1))*100)
    print('Taxa de sucesso:', success/(i+1)*100)
    
   

#30% de sucesso com vento
#98.3% de sucesso sem vento