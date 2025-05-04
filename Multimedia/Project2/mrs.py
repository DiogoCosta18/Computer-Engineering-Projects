import librosa
import librosa.display
import librosa.beat
import sounddevice as sd
import warnings
import numpy as np
import matplotlib.pyplot as plt
import os
import scipy.stats as stats
import scipy

music_dir = "../AllMusics"
queries_dir = "./Queries"
results_dir = "./resultados_TP2"

def features_array():
    return {
        "mfcc": [],
        "spectral_centroid": [],
        "spectral_bandwidth": [],
        "spectral_contrast": [],
        "spectral_flatness": [],
        "spectral_rolloff": [],
        "f0": [],
        "rms": [],
        "zero_crossing_rate": [],
        "tempo": []
    }

def extracting_features_and_stats(music_dir):
    all_features = []
    super_stats = []
    song = 1
    i = 0
    for file in os.listdir(music_dir):
        all_stats = np.zeros(190)
        print(f"Processing song {song}...")
        song += 1
        if file.endswith(".mp3"):
            file_path = os.path.join(music_dir, file)
            y, sr = librosa.load(file_path, sr=22050, mono=True)

            # Criar um dicionário para armazenar as features da música atual
            song_features = {}

            # Spectral features
            song_features["mfcc"] = np.array(librosa.feature.mfcc(y=y, sr=sr, n_mfcc=13)) # Valor de mfcc 13 pois é o padrão, 20 é a omissão
            song_features["spectral_centroid"] = np.array(librosa.feature.spectral_centroid(y=y,)[0, :])
            song_features["spectral_bandwidth"] = np.array(librosa.feature.spectral_bandwidth(y=y,)[0, :])
            song_features["spectral_contrast"] = np.array(librosa.feature.spectral_contrast(y=y,))
            song_features["spectral_flatness"] = np.array(librosa.feature.spectral_flatness(y=y,)[0, :])
            song_features["spectral_rolloff"] = np.array(librosa.feature.spectral_rolloff(y=y,)[0, :])

            # Temporal features
            f0 =  np.array(librosa.yin(y=y, fmin = 20, fmax = 11025)) # fmin - Número mínimo de Hz ouvidos pelo humano | fmax - metade da freq de amostragem
            f0[f0 == 11025] = 0
            song_features["f0"] = f0
            song_features["rms"] = np.array(librosa.feature.rms(y=y)[0, :])
            song_features["zero_crossing_rate"] = np.array(librosa.feature.zero_crossing_rate(y=y)[0, :])

            # Other features
            tempo = librosa.feature.tempo(y=y)
            song_features["tempo"] = tempo[0]

            # Adiciona as features ao array de stats
            all_features.append(song_features)
            
            for key, value in song_features.items():
                if key == "mfcc":
                    for i in range(value.shape[0]):
                        mfcc_stats = calculate_statistics(value[i])
                        all_stats[(i)*7:(i+1)*7] = np.array(mfcc_stats)
                elif key == "spectral_centroid":
                    stats = calculate_statistics(value)
                    all_stats[91:98] = np.array(stats)
                elif key == "spectral_bandwidth":
                    spectral_bandwidth = calculate_statistics(value)
                    all_stats[98:105] = np.array(spectral_bandwidth)
                elif key == "spectral_contrast":
                    for i in range(value.shape[0]):
                        spectral_contrast = calculate_statistics(value[i])
                        all_stats[105+(i)*7:105+(i+1)*7] = np.array(spectral_contrast)
                elif key == "spectral_flatness":
                    spectral_flatness = calculate_statistics(value)
                    all_stats[154:161] = np.array(spectral_flatness)
                elif key == "spectral_rolloff":
                    spectral_rolloff = calculate_statistics(value)
                    all_stats[161:168] = np.array(spectral_rolloff)
                elif key == "f0":
                    f0_stats = calculate_statistics(value)
                    all_stats[168:175] = np.array(f0_stats)
                elif key == "rms":
                    rms_stats = calculate_statistics(value)
                    all_stats[175:182] = np.array(rms_stats)
                elif key == "zero_crossing_rate":
                    zero_crossing_rate_stats = calculate_statistics(value)
                    all_stats[182:189] = np.array(zero_crossing_rate_stats)
                elif key == "tempo":
                    all_stats[189] = value

        super_stats.append(all_stats.tolist())
        #print(super_stats[i])
        i += 1

    return all_features, super_stats

def calculate_statistics(feature_array):

    mean = np.mean(feature_array)
    std = np.std(feature_array)
    skewness = scipy.stats.skew(feature_array)
    kurtosis = scipy.stats.kurtosis(feature_array)
    median = np.median(feature_array)
    min_val = np.min(feature_array)
    max_val = np.max(feature_array)

    return [mean, std, skewness, kurtosis,median, max_val, min_val]

def normalize_features(features_array, min_values=None, max_values=None):
    
    features_array = np.array(features_array)
    print(features_array.shape)

    # Min and Max of each row
    min_values = np.min(features_array, axis=0)
    max_values = np.max(features_array, axis=0)
    
    # Impedir divisao por 0
    range_values = max_values - min_values
    range_values = np.array(range_values)  # Ensure range_values is an array
    range_values[range_values == 0] = 1
    
    # (x - min) / (max - min)
    b = (features_array - min_values) / range_values
    
    return b, min_values, max_values

# Calculate spectral centroid
# y -> audio, sr -> sampling rate, frame_length -> length of the FFT window, hop_length -> sobreposição entre janelas
def calculate_spectral_centroid(y, sr, frame_length, hop_length):
    # Pading
    padding = frame_length - len(y) % frame_length
    y_padded = np.pad(y, (0, padding), mode='constant')

    # Nº janelas
    num_frames = (len(y_padded) - frame_length) // hop_length + 1

    spectral_centroids = np.zeros(num_frames)

    for n in range(num_frames):
        # Janela
        start = n * hop_length
        end = start + frame_length
        frame = y_padded[start:end]
        
        # Hanning
        window = np.hanning(frame_length)
        frame_windowed = frame * window
        
        # FFT
        fft_frame = scipy.fft.rfft(frame_windowed)
        fft_magnitude = np.abs(fft_frame)
        
        # sr/2 -> Teorema de Nyquist
        # Frequências associadas ao indice do espetro
        frequencies = np.linspace(0, sr / 2, len(fft_magnitude))
        # Fórmula do centroide espectral
        spectral_centroids[n] = np.sum(frequencies * fft_magnitude) / np.sum(fft_magnitude)

    return spectral_centroids

def compare_spectral_centroids(y, sr, frame_length, hop_length, output_file="spectral_centroid_error_metrics.csv"):
    # Calculate our version of spectral centroid
    spectral_centroid_custom = calculate_spectral_centroid(y, sr, frame_length, hop_length)

    # Calculate spectral centroid using librosa
    spectral_centroid_librosa = np.array(librosa.feature.spectral_centroid(y=y, sr=sr, n_fft=frame_length, hop_length=hop_length)[0, :])
    
    # Trim librosa's output to match the length of the custom implementation
    spectral_centroid_librosa_trimmed = spectral_centroid_librosa[2:]
    spectral_centroid_custom_trimmed = spectral_centroid_custom[:-3]

    # Trim values to 6 decimal places
    spectral_centroid_librosa_trimmed = np.round(spectral_centroid_librosa_trimmed, 6)
    spectral_centroid_custom_trimmed = np.round(spectral_centroid_custom_trimmed, 6)

    print(f"Length of Librosa: {len(spectral_centroid_librosa_trimmed)}")
    print(f"Length of Custom: {len(spectral_centroid_custom_trimmed)}")

    # Ensure both arrays are the same length
    min_length = min(spectral_centroid_custom_trimmed.size, spectral_centroid_librosa_trimmed.size)

    print(f"Custom Spectral Centroid: {spectral_centroid_custom_trimmed[0:min_length]}")
    print(f"Librosa Spectral Centroid: {spectral_centroid_librosa_trimmed[0:min_length]}")
    print(f"Length of Custom: {len(spectral_centroid_custom_trimmed[0:min_length])}")
   
    # Evaluate
    pearson_correlation = np.corrcoef(spectral_centroid_custom_trimmed[0:min_length], spectral_centroid_librosa_trimmed[0:min_length])[0, 1]
    rmse = np.sqrt(np.mean((spectral_centroid_custom_trimmed[0:min_length] - spectral_centroid_librosa_trimmed[0:min_length]) ** 2))/100

    print(f"Pearson Correlation Coefficient: {pearson_correlation}")
    print(f"RMSE: {rmse}")
    
    # Append error metrics to the output file
    with open(output_file, "a") as f:
        f.write(f"{pearson_correlation:.6f},{rmse:.6f}\n")

def euclidean_distance(vec1, vec2):
    return np.linalg.norm(vec1 - vec2)

def manhattan_distance(vec1, vec2):
    return np.sum(np.abs(vec1 - vec2))

def cosine_distance(vec1, vec2):
    dot_product = np.dot(vec1, vec2)
    norm_vec1 = np.linalg.norm(vec1)
    norm_vec2 = np.linalg.norm(vec2)
    if norm_vec1 == 0 or norm_vec2 == 0:
        return 1 
    cosine_similarity = dot_product / (norm_vec1 * norm_vec2)
    return 1 - cosine_similarity

# Gerar ranking para a query
def get_similarity_ranking(query_vec, features, distance_func, top_n=10):
    distances = [distance_func(query_vec, feat) for feat in features]
    ranked_indices = np.argsort(distances)[1:top_n+1]
    return ranked_indices, np.array(distances)[ranked_indices]

# Gerar ranking para a query
def calculate_similarity(query_vec, features, distance_func, top_n=10):
    distances = [distance_func(query_vec, feat) for feat in features]
    return distances

def calculate_features():
    warnings.filterwarnings("ignore")
    extracted_features, all_stats = extracting_features_and_stats(music_dir)

    querie_features, querie_stats = extracting_features_and_stats(queries_dir)

    # Save to CSV
    with open("features2.csv", 'w') as f:        
        # Escrever as features normalizadas
        np.savetxt(f, all_stats, delimiter=",", fmt="%.8f")
    
    # Normalize
    normalized_features, min_vals, max_vals = normalize_features(all_stats)

    normalized_querie_features, _ , _ = normalize_features(querie_stats, min_vals, max_vals)

    # Save to CSV
    with open("normalized_features2.csv", 'w') as f:
        # Escrever mínimos e máximos
        np.savetxt(f, [min_vals], delimiter=",", fmt="%.8f")
        np.savetxt(f, [max_vals], delimiter=",", fmt="%.8f")
        
        # Escrever as features normalizadas
        np.savetxt(f, normalized_features, delimiter=",", fmt="%.8f")

    # Clear the output file before appending new results
    with open("spectral_centroid_error_metrics.csv", "w") as f:
        f.write("Pearson Correlation,RMSE\n")

    for file in os.listdir(music_dir):
        if file.endswith(".mp3"):
            file_path = os.path.join(music_dir, file)
            y, sr = librosa.load(file_path, sr=22050, mono=True)
            compare_spectral_centroids(y, sr, frame_length=2048, hop_length=512, output_file="spectral_centroid_error_metrics.csv")

if __name__ == "__main__":
    
    # Carregar features normalizadas e min/max
    normalized_features = np.loadtxt("resultados_TP2/FM_All.csv", delimiter=",", skiprows=2)
    min_vals = np.loadtxt("resultados_TP2/FM_All.csv", delimiter=",", max_rows=1)
    max_vals = np.loadtxt("resultados_TP2/FM_All.csv", delimiter=",", skiprows=1, max_rows=1)

    normalized_query = np.loadtxt("resultados_TP2/FM_Q.csv", delimiter=",", skiprows=2)

    # Gerar matrizes
    for name, func in [("euclidean", euclidean_distance), ("manhattan", manhattan_distance), ("cosine", cosine_distance)]:
        distances = calculate_similarity(normalized_query, normalized_features, func, top_n=10)
        np.savetxt(f"{name}_similarity.csv", distances, fmt="%.6f")

    with open("ranking_results.txt", "w") as f:
        print(f"")

    # Gerar rankings
    for name, func in [("euclidean", euclidean_distance), ("manhattan", manhattan_distance), ("cosine", cosine_distance)]:
        ranking, distances = get_similarity_ranking(normalized_query, normalized_features, func, top_n=10)
        with open("ranking_results.txt", "a") as f:
            f.write(f"Top 10 for {name}:\n")
            for idx, dist in zip(ranking, distances):
                file_name = os.listdir(music_dir)[idx]
                print(f"Index: {idx}, File: {file_name}, Distância: {dist:.4f}")
                # Salvar ranking em ficheiro
                f.write(f"Index: {idx}, File: {file_name}, Distance: {dist:.6f}\n")
            f.write("\n")