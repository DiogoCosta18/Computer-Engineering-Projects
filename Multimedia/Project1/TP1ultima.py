import matplotlib.pyplot as plt
import numpy as np
import cv2
from scipy.fftpack import dct, idct
import matplotlib.colors as clr

cmapRED = clr.LinearSegmentedColormap.from_list("Red", [(0,0,0), (1,0,0)], N=256)
cmapBLUE = clr.LinearSegmentedColormap.from_list("Blue", [(0,0,0), (0,0,1)], N=256)
cmapGREEN = clr.LinearSegmentedColormap.from_list("Green", [(0,0,0), (0,1,0)], N=256)
cmapGREY = clr.LinearSegmentedColormap.from_list("Grey", [(0,0,0), (1,1,1)], N=256)

matrix_RGB_YCbCr = [[0.299, 0.587, 0.114], [-0.168736, -0.331264, 0.5], [0.5, -0.418688, -0.081312]]
                                                 
def load_image(image_path):
    img = cv2.imread(image_path)
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def showImage(img, title, cm=None):
    plt.figure()
    plt.imshow(img, cmap=cm)
    plt.axis('off')
    plt.title(title)
    plt.show()

def padding(image):
    h, w, _ = image.shape
    h_pad = 32 - (h % 32) if h % 32 != 0 else 0
    w_pad = 32 - (w % 32) if w % 32 != 0 else 0
    padded_image = np.pad(image, ((0, h_pad), (0, w_pad), (0, 0)), mode='edge')
    return padded_image, image.shape

def remove_padding(padded_image, original_shape):
    return padded_image[:original_shape[0], :original_shape[1], :]

def RGBtoYCbCr(R, G, B):
    ycbcrMatrix = np.array(matrix_RGB_YCbCr)
    rgbMatrix = np.stack((R, G, B), axis=-1)
    YCbCr = np.tensordot(rgbMatrix, ycbcrMatrix, axes=([2], [1]))
    YCbCr[:, :, 1:] += 128
    return YCbCr[:,:,0], YCbCr[:,:,1], YCbCr[:,:,2]

def YCbCrtoRGB(Y, Cb, Cr):
    YCbCr = np.stack((Y, Cb - 128, Cr - 128), axis=-1)
    rgbMatrix = np.linalg.inv(matrix_RGB_YCbCr)
    RGB_float = np.tensordot(YCbCr, rgbMatrix, axes=([2], [1]))
    RGB = np.round(np.clip(RGB_float, 0, 255)).astype(np.uint8)
    return RGB[:,:,0], RGB[:,:,1], RGB[:,:,2]

def right_factors(cb_factor, cr_factor):
    if cb_factor == 0 or cb_factor == 2 or cb_factor == 4 or cb_factor == 1:
        if cr_factor == 2 or cr_factor == 4 or cr_factor == 1:
            return True
    return False

def downSampling(Y, Cb, Cr, cb_factor, cr_factor, method=cv2.INTER_CUBIC):
    if not right_factors(cb_factor, cr_factor):
        return None
    
    if cb_factor == 0:
        cb_factor = cr_factor
        # 4:2:0 downsampling (horizontal and vertical)
        Cb_d = cv2.resize(Cb, (Cb.shape[1] // cb_factor, Cb.shape[0] // cb_factor), interpolation=method)
        Cr_d = cv2.resize(Cr, (Cr.shape[1] // cb_factor, Cr.shape[0] // cb_factor), interpolation=method)
    else:
        # Others downsampling (horizontal only)
        Cb_d = cv2.resize(Cb, (Cb.shape[1] // cb_factor, Cb.shape[0]), interpolation=method)
        Cr_d = cv2.resize(Cr, (Cr.shape[1] // cr_factor, Cr.shape[0]), interpolation=method)
    return Y, Cb_d, Cr_d

def upSampling(Y, Cb, Cr, cb_factor, cr_factor, method=cv2.INTER_CUBIC):
    if not right_factors(cb_factor, cr_factor):
        return None

    if cb_factor == 0:
        cb_factor = cr_factor
        # 4:2:0 upsampling (horizontal and vertical)
        Cb_u = cv2.resize(Cb, (Cb.shape[1] * cb_factor, Cb.shape[0] * cb_factor), interpolation=method)
        Cr_u = cv2.resize(Cr, (Cr.shape[1] * cb_factor, Cr.shape[0] * cb_factor), interpolation=method)
    else:
        # Others upsampling (horizontal only)
        Cb_u = cv2.resize(Cb, (Cb.shape[1] * cb_factor, Cb.shape[0]), interpolation=method)
        Cr_u = cv2.resize(Cr, (Cr.shape[1] * cr_factor, Cr.shape[0]), interpolation=method)
    return Y, Cb_u, Cr_u

def apply_dct(Y, Cb, Cr):
    Y_dct = dct(dct(Y, norm="ortho").T, norm="ortho").T
    Cb_dct = dct(dct(Cb, norm="ortho").T, norm="ortho").T
    Cr_dct = dct(dct(Cr, norm="ortho").T, norm="ortho").T
    return Y_dct, Cb_dct, Cr_dct

def apply_idct(Y_dct, Cb_dct, Cr_dct):
    Y = idct(idct(Y_dct, norm="ortho").T, norm="ortho").T
    Cb = idct(idct(Cb_dct, norm="ortho").T, norm="ortho").T
    Cr = idct(idct(Cr_dct, norm="ortho").T, norm="ortho").T
    return Y, Cb, Cr

def apply_dct_blocks(channel, block_size):
    h, w = channel.shape
    dct_channel = np.zeros_like(channel, dtype=float)
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            block = channel[i:i+block_size, j:j+block_size]
            dct_block = dct(dct(block, norm="ortho").T, norm="ortho").T
            dct_channel[i:i+block_size, j:j+block_size] = dct_block
    return dct_channel

def apply_idct_blocks(dct_channel, block_size):
    h, w = dct_channel.shape
    channel = np.zeros_like(dct_channel, dtype=float)
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            dct_block = dct_channel[i:i+block_size, j:j+block_size]
            block = idct(idct(dct_block, norm="ortho").T, norm="ortho").T
            channel[i:i+block_size, j:j+block_size] = block
    return channel

def visualize_dct(dct_channel, title):
    plt.figure()
    plt.imshow(np.log(np.abs(dct_channel) + 0.0001), cmap='gray')
    plt.axis('off')
    plt.title(title)
    plt.colorbar()
    plt.show()


def quantization_matrix(quality_factor):
    # Matriz de quantização padrão para Y (luminância)
    Qy = np.array([[16, 11, 10, 16, 24, 40, 51, 61],
                   [12, 12, 14, 19, 26, 58, 60, 55],
                   [14, 13, 16, 24, 40, 57, 69, 56],
                   [14, 17, 22, 29, 51, 87, 80, 62],
                   [18, 22, 37, 56, 68, 109, 103, 77],
                   [24, 35, 55, 64, 81, 104, 113, 92],
                   [49, 64, 78, 87, 103, 121, 120, 101],
                   [72, 92, 95, 98, 112, 100, 103, 99]])

    # Matriz de quantização padrão para CbCr (crominância)
    Qc = np.array([[17, 18, 24, 47, 99, 99, 99, 99],
                   [18, 21, 26, 66, 99, 99, 99, 99],
                   [24, 26, 56, 99, 99, 99, 99, 99],
                   [47, 66, 99, 99, 99, 99, 99, 99],
                   [99, 99, 99, 99, 99, 99, 99, 99],
                   [99, 99, 99, 99, 99, 99, 99, 99],
                   [99, 99, 99, 99, 99, 99, 99, 99],
                   [99, 99, 99, 99, 99, 99, 99, 99]])

    # Ajuste da matriz de quantização de acordo com o fator de qualidade (slides)
    if quality_factor < 50:
        scale = 50 / quality_factor
    else:
        scale = (100 - quality_factor) / 50
    
    if scale == 0:
        Qy = np.ones((8, 8))
        Qc = np.ones((8, 8))
    else:
        Qy = np.clip(np.round((Qy * scale)), 1, 255).astype(np.uint8)
        Qc = np.clip(np.round((Qc * scale)), 1, 255).astype(np.uint8)
    return Qy, Qc

def quantize_dct(channel, is_Y: bool, quality_factor, block_size=8):
    Qy, Qc = quantization_matrix(quality_factor)
    h, w = channel.shape 
    quantize_channel = np.zeros_like(channel, dtype=np.int32)

    # 8x8 blocks
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            if is_Y == True:
                quantize_channel[i:i+8, j:j+8] = np.round((channel[i:i+8, j:j+8] / Qy)).astype(np.int32)
            else:
                quantize_channel[i:i+8, j:j+8] = np.round((channel[i:i+8, j:j+8] / Qc)).astype(np.int32)

    return quantize_channel


def dequantize_dct(channel, is_Y: bool, quality_factor, block_size=8):
    Qy, Qc = quantization_matrix(quality_factor)
    h, w = channel.shape
    dequantize_channel = np.zeros_like(channel, dtype=np.float32)

    # 8x8 blocks
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            if is_Y == True:
                dequantize_channel[i:i+8, j:j+8] = (channel[i:i+8, j:j+8] * Qy).astype(np.float32)
            else:
                dequantize_channel[i:i+8, j:j+8] = (channel[i:i+8, j:j+8] * Qc).astype(np.float32)

    return dequantize_channel

def apply_custom_colormap(image, colormap, channel):
    normalized_image = image / 255.0
    colormap_image = colormap(normalized_image[:,:,channel])[:, :] 
    return colormap_image


def visualize_image_with_colormap(image, colormap, channel=0):
    colormap_image = apply_custom_colormap(image, colormap, channel)
    showImage(colormap_image, "Colormap Image")

def split_into_rgb_components(image):
    return image[:,:,0], image[:,:,1], image[:,:,2]

def combine_rgb_components(r, g, b):
    return np.stack((r, g, b), axis=-1)

def visualize_rgb_components(r, g, b):
    showImage(r, 'Red Channel', cm='Reds')
    showImage(g, 'Green Channel', cm='Greens')
    showImage(b, 'Blue Channel', cm='Blues')

def showImgSubMatrix(img, ln, col, dim, ch=None):
# img is the image ; Ln is the line ; col is the column ; dim is the dimension (Length to show) ; ch is the channel (RGB)
    if ch == None:
        print (img[ln:ln+dim, col:col+dim]," \n")
    else:
        print (img[ln:ln+dim, col:col+dim, ch]," \n")

# Metrics
def calculate_mse(original, reconstructed):
    return np.mean((original - reconstructed) ** 2) * 3

def calculate_rmse(mse):
    return np.sqrt(mse)

def calculate_snr(original, mse):
    signal_power = np.mean(original ** 2)
    return 10 * np.log10(signal_power / mse) if mse > 0 else float('inf')

def calculate_psnr(original, mse, max_pixel_value=255):
    return 20 * np.log10(max_pixel_value) - 10 * np.log10(mse) if mse > 0 else float('inf')

def calculate_max_avg_diff(original, reconstructed):
    diff = np.abs(original - reconstructed)
    max_diff = np.max(diff)
    avg_diff = np.mean(diff)
    return max_diff, avg_diff


def dpcm(quantized_channel, block_size=8):
    
    h, w = quantized_channel.shape
    dpcm_channel = quantized_channel.copy()
    
    #DC Inicial
    prev_dc = 0
    
    
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            #Coeficiente DC
            current_dc = dpcm_channel[i, j]
            
            #DC Novo = Atual - Anterior
            dpcm_channel[i, j] = current_dc - prev_dc
            
            #Novo Anterior
            prev_dc = current_dc
    
    return dpcm_channel

def dpcmInv(dpcm_channel, block_size=8):
    
    h, w = dpcm_channel.shape
    restored_channel = dpcm_channel.copy()
    
    #DC 
    accumulated_dc = 0
    
    
    for i in range(0, h, block_size):
        for j in range(0, w, block_size):
            #DPCM do Coeficiente
            current_dc = restored_channel[i, j]
            
            #DC Original
            accumulated_dc += current_dc
            
            #Restaura o coeficiente DC original
            restored_channel[i, j] = accumulated_dc
    
    return restored_channel
           
def encoder(image, block_size, quality_factor, cb_factor, cr_factor):
    # 3.1 Visualize RGB
    showImage(image, "Original Image (RGB)")

    user_colormap = cmapRED
    visualize_image_with_colormap(image, user_colormap, 0)

    user_colormap = cmapGREEN
    visualize_image_with_colormap(image, user_colormap, 1)

    user_colormap = cmapBLUE
    visualize_image_with_colormap(image, user_colormap, 2)
    
    # 4.1 Padding
    padded_image, original_shape = padding(image)
    showImage(padded_image, "Padded Image (RGB)")
    print("Padding")
    showImgSubMatrix(padded_image, 8, 8, 8)

    # 5.1 RGB to YCbCr
    r, g, b = split_into_rgb_components(padded_image)

    #showImage(r, 'Red Channel', cm='Reds')
    #showImage(g, 'Green Channel', cm='Greens')
    #showImage(b, 'Blue Channel', cm='Blues')

    y, cb, cr = RGBtoYCbCr(r, g, b)
    #showImage(y, 'Y Channel', cmapGREY)
    #showImage(cb, 'Cb Channel', cmapGREY)
    #showImage(cr, 'Cr Channel', cmapGREY)
    print("YCbCr")
    showImgSubMatrix(y, 8, 8, 8)
    showImgSubMatrix(cb, 8, 8, 8)
    
    # 6.1 Downsampling
    # downSampling com taxa 4:2:0
    Y_d_420, Cb_d_420, Cr_d_420 = downSampling(y, cb, cr, cb_factor=0, cr_factor=2)
    print(f"Dimensões após downsampling 4:2:0 - Y: {Y_d_420.shape}, Cb: {Cb_d_420.shape}, Cr: {Cr_d_420.shape}")
    showImage(Y_d_420, 'Y Channel Downsampling 4:2:0', cmapGREY)
    showImage(Cb_d_420, 'Cb Channel Downsampling 4:2:0', cmapGREY)
    showImage(Cr_d_420, 'Cr Channel Downsampling 4:2:0', cmapGREY)

    # downSampling com taxa 4:2:2
    y_d, cb_d, cr_d = downSampling(y, cb, cr, cb_factor=2, cr_factor=2)
    print(f"Dimensões após downsampling 4:2:2 - Y: {y_d.shape}, Cb: {cb_d.shape}, Cr: {cr_d.shape}")
    showImage(y_d, 'Y Channel Downsampling 4:2:2', cmapGREY)
    showImage(cb_d, 'Cb Channel Downsampling 4:2:2', cmapGREY)
    showImage(cr_d, 'Cr Channel Downsampling 4:2:2', cmapGREY)
    print("Downsampling")
    showImgSubMatrix(cb, 8, 8, 8)

    # 7.1 DCT
    #Blocks 1x1
    Y_dct_1, Cb_dct_1, Cr_dct_1 = apply_dct(y_d, cb_d, cr_d)
    #visualize_dct(Y_dct_1, "Y Channel (DCT)")
    #visualize_dct(Cb_dct_1, "Cb Channel (DCT)")
    #visualize_dct(Cr_dct_1, "Cr Channel (DCT)")

    #Blocks 8x8
    y_dct = apply_dct_blocks(y_d, block_size)
    cb_dct = apply_dct_blocks(cb_d, block_size)
    cr_dct = apply_dct_blocks(cr_d, block_size)
    visualize_dct(y_dct, "Y Channel (DCT)")
    visualize_dct(cb_dct, "Cb Channel (DCT)")
    visualize_dct(cr_dct, "Cr Channel (DCT)")
    print("DCT 8x8")
    showImgSubMatrix(y_dct, 8, 8, 8)


    #Blocks 64x64
    y_dct_64 = apply_dct_blocks(y_d, 64)
    cb_dct_64 = apply_dct_blocks(cb_d, 64)
    cr_dct_64 = apply_dct_blocks(cr_d, 64)
    #visualize_dct(y_dct_64, "Y Channel (DCT)")
    #visualize_dct(cb_dct_64, "Cb Channel (DCT)")
    #visualize_dct(cr_dct_64, "Cr Channel (DCT)")

    # 8.1 Quantization
    Qy, Qc = quantization_matrix(quality_factor = 75)
    print ("QY and QC with QF = 75: \n", Qy, "\n", Qc)

    # General visualization
    y_q = quantize_dct(y_dct, True, quality_factor) 
    cb_q = quantize_dct(cb_dct, False, quality_factor)
    cr_q = quantize_dct(cr_dct, False, quality_factor)
    visualize_dct(y_q, "Y Channel (Quantized DCT)")
    visualize_dct(cb_q, "Cb Channel (Quantized DCT)")
    visualize_dct(cr_q, "Cr Channel (Quantized DCT)")
    print ("Y_Q: ")
    showImgSubMatrix(y_q, 8, 8, 8)

    # Quality factor = 10
    y_q_10 = quantize_dct(y_dct, True, 10)
    cb_q_10 = quantize_dct(cb_dct, False, 10)
    cr_q_10 = quantize_dct(cr_dct, False, 10)
    #visualize_dct(y_q_10, "Y Channel (Quantized DCT) QF=10")
    #visualize_dct(cb_q_10, "Cb Channel (Quantized DCT) QF=10")
    #visualize_dct(cr_q_10, "Cr Channel (Quantized DCT) QF=10")

    # Quality factor = 25
    y_q_25 = quantize_dct(y_dct, True, 25)
    cb_q_25 = quantize_dct(cb_dct, False, 25)
    cr_q_25 = quantize_dct(cr_dct, False, 25)
    #visualize_dct(y_q_25, "Y Channel (Quantized DCT) QF=25")
    #visualize_dct(cb_q_25, "Cb Channel (Quantized DCT) QF=25")
    #visualize_dct(cr_q_25, "Cr Channel (Quantized DCT) QF=25")

    # Quality factor = 50
    y_q_50 = quantize_dct(y_dct, True, 50)
    cb_q_50 = quantize_dct(cb_dct, False, 50)
    cr_q_50 = quantize_dct(cr_dct, False, 50)
    #visualize_dct(y_q_50, "Y Channel (Quantized DCT) QF=50")
    #visualize_dct(cb_q_50, "Cb Channel (Quantized DCT) QF=50")
    #visualize_dct(cr_q_50, "Cr Channel (Quantized DCT) QF=50")

    # Quality factor = 75
    y_q_75 = quantize_dct(y_dct, True, 75)
    cb_q_75 = quantize_dct(cb_dct, False, 75)
    cr_q_75 = quantize_dct(cr_dct, False, 75)
    #visualize_dct(y_q_75, "Y Channel (Quantized DCT) QF=75")
    #visualize_dct(cb_q_75, "Cb Channel (Quantized DCT) QF=75")
    #visualize_dct(cr_q_75, "Cr Channel (Quantized DCT) QF=75")

    # Quality factor = 100
    y_q_100 = quantize_dct(y_dct, True, 100)
    cb_q_100 = quantize_dct(cb_dct, False, 100)
    cr_q_100 = quantize_dct(cr_dct, False, 100)
    #visualize_dct(y_q_100, "Y Channel (Quantized DCT) QF=100")
    #visualize_dct(cb_q_100, "Cb Channel (Quantized DCT) QF=100")
    #visualize_dct(cr_q_100, "Cr Channel (Quantized DCT) QF=100")
    
    #9.1 DPCM
    y_dpcm = dpcm(y_q, block_size)
    cb_dpcm = dpcm(cb_q, block_size)
    cr_dpcm = dpcm(cr_q, block_size)
    visualize_dct(y_dpcm, f"Y Channel (DPCM DC Coefficients) QF={quality_factor}")
    visualize_dct(cb_dpcm, f"Cb Channel (DPCM DC Coefficients) QF={quality_factor}")
    visualize_dct(cr_dpcm, f"Cr Channel (DPCM DC Coefficients) QF={quality_factor}")
    print(f"Yb_DPCM:")
    showImgSubMatrix(y_dpcm, 8, 8, 8)
    
    # DPCM com QF=10
    y_dpcm_10 = dpcm(y_q_10, block_size)
    cb_dpcm_10 = dpcm(cb_q_10, block_size)
    cr_dpcm_10 = dpcm(cr_q_10, block_size)
    #visualize_dct(y_dpcm_10, "Y Channel (DPCM DC Coefficients) QF=10")
    #visualize_dct(cb_dpcm_10, "Cb Channel (DPCM DC Coefficients) QF=10")
    #visualize_dct(cr_dpcm_10, "Cr Channel (DPCM DC Coefficients) QF=10")
    
    # DPCM com QF=25
    y_dpcm_25 = dpcm(y_q_25, block_size)
    cb_dpcm_25 = dpcm(cb_q_25, block_size)
    cr_dpcm_25 = dpcm(cr_q_25, block_size)
    #visualize_dct(y_dpcm_25, "Y Channel (DPCM DC Coefficients) QF=25")
    #visualize_dct(cb_dpcm_25, "Cb Channel (DPCM DC Coefficients) QF=25")
    #visualize_dct(cr_dpcm_25, "Cr Channel (DPCM DC Coefficients) QF=25")
    
    # DPCM com QF=50
    y_dpcm_50 = dpcm(y_q_50, block_size)
    cb_dpcm_50 = dpcm(cb_q_50, block_size)
    cr_dpcm_50 = dpcm(cr_q_50, block_size)
    #visualize_dct(y_dpcm_50, "Y Channel (DPCM DC Coefficients) QF=50")
    #visualize_dct(cb_dpcm_50, "Cb Channel (DPCM DC Coefficients) QF=50")
    #visualize_dct(cr_dpcm_50, "Cr Channel (DPCM DC Coefficients) QF=50")
    
    # DPCM com QF=75
    y_dpcm_75 = dpcm(y_q_75, block_size)
    cb_dpcm_75 = dpcm(cb_q_75, block_size)
    cr_dpcm_75 = dpcm(cr_q_75, block_size)
    #visualize_dct(y_dpcm_75, "Y Channel (DPCM DC Coefficients) QF=75")
    #visualize_dct(cb_dpcm_75, "Cb Channel (DPCM DC Coefficients) QF=75")
    #visualize_dct(cr_dpcm_75, "Cr Channel (DPCM DC Coefficients) QF=75")
    
    # DPCM com QF=100
    y_dpcm_100 = dpcm(y_q_100, block_size)
    cb_dpcm_100 = dpcm(cb_q_100, block_size)
    cr_dpcm_100 = dpcm(cr_q_100, block_size)
    #visualize_dct(y_dpcm_100, "Y Channel (DPCM DC Coefficients) QF=100")
    #visualize_dct(cb_dpcm_100, "Cb Channel (DPCM DC Coefficients) QF=100")
    #visualize_dct(cr_dpcm_100, "Cr Channel (DPCM DC Coefficients) QF=100")

    # Retorna os dados para o fator de qualidade padrão (definido na chamada da função)
    return y_dpcm, cb_dpcm, cr_dpcm, original_shape, y

def decoder(y_dpcm, cb_dpcm, cr_dpcm, original_shape, block_size, quality_factor, cb_factor, cr_factor):

    # 9.2
    y_q = dpcmInv(y_dpcm, block_size)
    cb_q = dpcmInv(cb_dpcm, block_size)
    cr_q = dpcmInv(cr_dpcm, block_size)
    visualize_dct(y_q, f"Y Channel (Restored from DPCM) QF={quality_factor}")
    visualize_dct(cb_q, f"Cb Channel (Restored from DPCM) QF={quality_factor}")
    visualize_dct(cr_q, f"Cr Channel (Restored from DPCM) QF={quality_factor}")
    print(f"Restored from DPCM com QF={quality_factor}:")
    showImgSubMatrix(y_q, 8, 8, 8)

    # 8.2 Dequantization (block 8x8)
    y_d = dequantize_dct(y_q, True, quality_factor)
    cb_d = dequantize_dct(cb_q, False, quality_factor)
    cr_d = dequantize_dct(cr_q, False, quality_factor)
    visualize_dct(y_d, "Y Channel (Dequantized DCT)")
    visualize_dct(cb_d, "Cb Channel (Dequantized DCT)")
    visualize_dct(cr_d, "Cr Channel (Dequantized DCT)")
    print("Yb_iQ: ")
    showImgSubMatrix(y_d, 8, 8, 8)

    # Quality factor = 10
    y_d_10 = dequantize_dct(y_q, True, 10)
    cb_d_10 = dequantize_dct(cb_q, False, 10)
    cr_d_10 = dequantize_dct(cr_q, False, 10)
    visualize_dct(y_d_10, "Y Channel (Dequantized DCT) QF=10")
    visualize_dct(cb_d_10, "Cb Channel (Dequantized DCT) QF=10")
    visualize_dct(cr_d_10, "Cr Channel (Dequantized DCT) QF=10")

    # Quality factor = 25
    y_d_25 = dequantize_dct(y_q, True, 25)
    cb_d_25 = dequantize_dct(cb_q, False, 25)
    cr_d_25 = dequantize_dct(cr_q, False, 25)
    visualize_dct(y_d_25, "Y Channel (Dequantized DCT) QF=25")
    visualize_dct(cb_d_25, "Cb Channel (Dequantized DCT) QF=25")
    visualize_dct(cr_d_25, "Cr Channel (Dequantized DCT) QF=25")

    # Quality factor = 50
    y_d_50 = dequantize_dct(y_q, True, 50)
    cb_d_50 = dequantize_dct(cb_q, False, 50)
    cr_d_50 = dequantize_dct(cr_q, False, 50)
    visualize_dct(y_d_50, "Y Channel (Dequantized DCT) QF=50")
    visualize_dct(cb_d_50, "Cb Channel (Dequantized DCT) QF=50")
    visualize_dct(cr_d_50, "Cr Channel (Dequantized DCT) QF=50")

    # Quality factor = 75
    y_d_75 = dequantize_dct(y_q, True, 75)
    cb_d_75 = dequantize_dct(cb_q, False, 75)
    cr_d_75 = dequantize_dct(cr_q, False, 75)
    visualize_dct(y_d_75, "Y Channel (Dequantized DCT) QF=75")
    visualize_dct(cb_d_75, "Cb Channel (Dequantized DCT) QF=75")
    visualize_dct(cr_d_75, "Cr Channel (Dequantized DCT) QF=75")

    # Quality factor = 100
    y_d_100 = dequantize_dct(y_q, True, 100)
    cb_d_100 = dequantize_dct(cb_q, False, 100)
    cr_d_100 = dequantize_dct(cr_q, False, 100)
    visualize_dct(y_d_100, "Y Channel (Dequantized DCT) QF=100")
    visualize_dct(cb_d_100, "Cb Channel (Dequantized DCT) QF=100")
    visualize_dct(cr_d_100, "Cr Channel (Dequantized DCT) QF=100")


    # 7.2 Inverse DCT
    y_idct = apply_idct_blocks(y_d, block_size)
    cb_idct = apply_idct_blocks(cb_d, block_size)
    cr_idct = apply_idct_blocks(cr_d, block_size)

    # 6.2 Upsampling
    # UpSampling 4:2:2
    y_u, cb_u, cr_u = upSampling(y_idct, cb_idct, cr_idct, cb_factor=2, cr_factor=2)
    print(f"Dimensões após upsampling 4:2:2 - Y: {y_u.shape}, Cb: {cb_u.shape}, Cr: {cr_u.shape}")
    showImage(y_u, "Y (Upsampled 4:2:2)", cmapGREY)
    showImage(cb_u, "Cb (Upsampled 4:2:2)", cmapGREY)
    showImage(cr_u, "Cr (Upsampled 4:2:2)", cmapGREY)

    # 5.2 YCbCr to RGB
    r_reconstructed, g_reconstructed, b_reconstructed = YCbCrtoRGB(y_u, cb_u, cr_u)
    reconstructed_image = combine_rgb_components(r_reconstructed, g_reconstructed, b_reconstructed)
    showImgSubMatrix(r_reconstructed, 8, 8, 8)

    # 4.2 Remove Padding
    final_image = remove_padding(reconstructed_image, original_shape).astype(np.uint8)
    showImage(final_image, "Reconstructed Image")
    
    return final_image, y_u

if __name__ == '__main__':
    image_path = "./imagens/airport.bmp"
    image = load_image(image_path)
    block_size = 8
    quality_factor = 75
    cb_factor, cr_factor = 2, 2

    # Encoder
    y_dpcm, cb_dpcm, cr_dpcm, original_shape, y_original = encoder(image, block_size, quality_factor, cb_factor, cr_factor)

    # Decoder
    reconstructed_image, y_reconstructed = decoder(y_dpcm, cb_dpcm, cr_dpcm, original_shape, block_size, quality_factor, cb_factor, cr_factor)

    # Metrics
    image_metrics = image.astype(np.uint16)
    reconstructed_image_metrics = reconstructed_image.astype(np.uint16)
    max_diff, avg_diff = calculate_max_avg_diff(y_original, y_reconstructed)
    mse = calculate_mse(image_metrics, reconstructed_image_metrics)
    rmse = calculate_rmse(mse)
    snr = calculate_snr(image_metrics, mse)
    psnr = calculate_psnr(image_metrics, mse)
    print(f"MSE: {mse}")
    print(f"RMSE: {rmse}")
    print(f"SNR: {snr}")
    print(f"PSNR: {psnr}")
    print("Max Diff: ", max_diff)
    print("Avg Diff: ", avg_diff)
