# Author: Marco Simoes
# Adapted from Java's implementation of Rui Pedro Paiva
# Teoria da Informacao, LEI, 2022

import sys
import numpy as np
from huffmantree import HuffmanTree



class GZIPHeader:
	''' class for reading and storing GZIP header fields '''

	ID1 = ID2 = CM = FLG = XFL = OS = 0
	MTIME = []
	lenMTIME = 4
	mTime = 0

	# bits 0, 1, 2, 3 and 4, respectively (remaining 3 bits: reserved)
	FLG_FTEXT = FLG_FHCRC = FLG_FEXTRA = FLG_FNAME = FLG_FCOMMENT = 0   
	
	# FLG_FTEXT --> ignored (usually 0)
	# if FLG_FEXTRA == 1
	XLEN, extraField = [], []
	lenXLEN = 2
	
	# if FLG_FNAME == 1
	fName = ''  # ends when a byte with value 0 is read
	
	# if FLG_FCOMMENT == 1
	fComment = ''   # ends when a byte with value 0 is read
		
	# if FLG_HCRC == 1
	HCRC = []
		
		
	
	def read(self, f):
		''' reads and processes the Huffman header from file. Returns 0 if no error, -1 otherwise '''

		# ID 1 and 2: fixed values
		self.ID1 = f.read(1)[0]  
		if self.ID1 != 0x1f: return -1 # error in the header
			
		self.ID2 = f.read(1)[0]
		if self.ID2 != 0x8b: return -1 # error in the header
		
		# CM - Compression Method: must be the value 8 for deflate
		self.CM = f.read(1)[0]
		if self.CM != 0x08: return -1 # error in the header
					
		# Flags
		self.FLG = f.read(1)[0]
		
		# MTIME
		self.MTIME = [0]*self.lenMTIME
		self.mTime = 0
		for i in range(self.lenMTIME):
			self.MTIME[i] = f.read(1)[0]
			self.mTime += self.MTIME[i] << (8 * i) 				
						
		# XFL (not processed...)
		self.XFL = f.read(1)[0]
		
		# OS (not processed...)
		self.OS = f.read(1)[0]
		
		# --- Check Flags
		self.FLG_FTEXT = self.FLG & 0x01
		self.FLG_FHCRC = (self.FLG & 0x02) >> 1
		self.FLG_FEXTRA = (self.FLG & 0x04) >> 2
		self.FLG_FNAME = (self.FLG & 0x08) >> 3
		self.FLG_FCOMMENT = (self.FLG & 0x10) >> 4
					
		# FLG_EXTRA
		if self.FLG_FEXTRA == 1:
			# read 2 bytes XLEN + XLEN bytes de extra field
			# 1st byte: LSB, 2nd: MSB
			self.XLEN = [0]*self.lenXLEN
			self.XLEN[0] = f.read(1)[0]
			self.XLEN[1] = f.read(1)[0]
			self.xlen = self.XLEN[1] << 8 + self.XLEN[0]
			
			# read extraField and ignore its values
			self.extraField = f.read(self.xlen)
		
		def read_str_until_0(f):
			s = ''
			while True:
				c = f.read(1)[0]
				if c == 0: 
					return s
				s += chr(c)
		
		# FLG_FNAME
		if self.FLG_FNAME == 1:
			self.fName = read_str_until_0(f)
		
		# FLG_FCOMMENT
		if self.FLG_FCOMMENT == 1:
			self.fComment = read_str_until_0(f)
		
		# FLG_FHCRC (not processed...)
		if self.FLG_FHCRC == 1:
			self.HCRC = f.read(2)
			
		return 0
			



class GZIP:
	''' class for GZIP decompressing file (if compressed with deflate) '''

	gzh = None
	gzFile = ''
	fileSize = origFileSize = -1
	numBlocks = 0
	f = None
	

	bits_buffer = 0
	available_bits = 0		

	
	def __init__(self, filename):
		self.gzFile = filename
		self.f = open(filename, 'rb')
		self.f.seek(0,2)
		self.fileSize = self.f.tell()
		self.f.seek(0)

		
	

	def decompress(self):
		''' main function for decompressing the gzip file with deflate algorithm '''
		
		numBlocks = 0

		# get original file size: size of file before compression
		origFileSize = self.getOrigFileSize()
		print(origFileSize)
		
		# read GZIP header
		error = self.getHeader()
		if error != 0:
			print('Formato invalido!')
			return
		
		# show filename read from GZIP header
		print(self.gzh.fName)
		
		
		# MAIN LOOP - decode block by block
		BFINAL = 0	
		while not BFINAL == 1:	
			
			BFINAL = self.readBits(1)
							
			BTYPE = self.readBits(2)					
			if BTYPE != 2:
				print('Error: Block %d not coded with Huffman Dynamic coding' % (numBlocks+1))
				return
			
									
			#--- STUDENTS --- ADD CODE HERE
			# 
			# 
			HLIT, HDIST, HCLEN = self.readHuffmanDinamico()
			comprimentos_codigo_HCLEN = self.armazenar_comprimentos_codigos(HCLEN)
			huffman_codes_HCLEN = self.generate_huffman_codes(comprimentos_codigo_HCLEN)
			huffman_tree_HCLEN = self.buildHuffmanTree(huffman_codes_HCLEN)
			comprimentos_codigo_HLIT = self.search_bit_by_bit(huffman_tree_HCLEN, HLIT)
			comprimentos_codigo_HDIST = self.search_bit_by_bit(huffman_tree_HCLEN, HDIST)
			huffman_codes_HLIT = self.generate_huffman_codes(comprimentos_codigo_HLIT)
			huffman_codes_HDIST = self.generate_huffman_codes(comprimentos_codigo_HDIST)
			print("HCLEN: ",HCLEN, "\nHDIST: ", HDIST, "\nHLIT: ", HLIT)
			print("HCLEN CODES:\n", huffman_codes_HCLEN)
			print("HDIST CODES:\n", huffman_codes_HDIST)
			print("HLIT CODES:\n", huffman_codes_HLIT)
			huffman_tree_HLIT = self.buildHuffmanTree(huffman_codes_HLIT)
			huffman_tree_HDIST = self.buildHuffmanTree(huffman_codes_HDIST)
			texto = self.descodifica(huffman_tree_HLIT, huffman_tree_HDIST)
			self.escreveFicheiro(texto)																																			
			# update number of blocks read
			numBlocks += 1

		# close file			
		
		self.f.close()	
		print("End: %d block(s) analyzed." % numBlocks)

#------------------------------------Inicio do nosso codigo --------------------------------


	def readHuffmanDinamico(self):  #calcula HLIT, HDIST, HCLEN
		HLIT = 257 + self.readBits(5)
		HDIST = 1 + self.readBits(5)
		HCLEN = 4 + self.readBits(4)
		return HLIT, HDIST, HCLEN
	
	def armazenar_comprimentos_codigos(self, HCLEN): #Armazena num array os comprimentos dos códigos de HCLEN:
		# Sequencia de 3 bits fornecida e que vai ser lida usando o indice depois de fazermos o readBits(3)
		sequencia_3_bits = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15]

		# Array vazio para armazenar os comprimentos de codigos
		comprimentos_codigos = [0] * len(sequencia_3_bits)

		# Loop para ler HCLEN e armazenar os comprimentos no array
		for i in range(HCLEN):
			# Le 3 bits e usa o indice para escolher o simbolo no array sequencia_3_bits ao qual corresponde o 
			# comprimento lido que é guardado no comprimentos_codigos[simbolo]
			comprimento = self.readBits(3)
			comprimentos_codigos[sequencia_3_bits[i]] = comprimento

		return comprimentos_codigos
	
	def generate_huffman_codes(self, code_lengths ):#converte os comprimentos em códigos de Huffman
		bl_count = [0] * (max(code_lengths) + 1) #inicializa array com 0s
		for length in code_lengths: #conta quantas vezes é que cada valor ocorre dentro do array
			bl_count[length] += 1
		bl_count[0] = 0
		#encontra o valor númerico do menor código para cada code_lengths
		code = 0
		next_code = [0] * (max(code_lengths) + 1) #inicializa array com 0s
		for bits in range(1, max(code_lengths) + 1):
			code = (code + bl_count[bits - 1]) << 1
			next_code[bits] = code	
	
		huffman_codes = {}
		for i in range (len(code_lengths)):
			if code_lengths[i] != 0:
				huffman_codes[i] = bin(next_code[code_lengths[i]])[2:].zfill(code_lengths[i])
				next_code[code_lengths[i]] += 1

		return huffman_codes
	
	def buildHuffmanTree(self, huffman_codes):
    	# Constrói a árvore de Huffman com base nos comprimentos dos códigos
		huffman_tree = HuffmanTree()
		for i in huffman_codes:
			code = huffman_codes[i]
			huffman_tree.addNode(code,i)

		return huffman_tree
	
	def search_bit_by_bit(self, huffman_tree, HLIT):
		i=0
		huffman_codes = {}
		while i < HLIT:
			
			bit = str(self.readBits(1))
			code = huffman_tree.nextNode(bit)
			if code >= 0:#encontrou uma folha
				huffman_tree.resetCurNode()
				match code:#se for 16, 17 ou 18 tem de ler bits extra
					case 16:
						comprimento_extra = self.readBits(2)
						aux = 3 + comprimento_extra
						for k in range(aux): #copia o valor anterior de 3-6 vezes
							huffman_codes[i+k] = huffman_codes[i-1]
						i += aux
						
					case 17:#avança 3-10 vezes deixando a 0s o comprimento
						comprimento_extra = self.readBits(3)
						i += 3 + comprimento_extra
					case 18:#avança 11-138 vezes deixando a 0s o comprimento
						comprimento_extra = self.readBits(7)
						i += 11 + comprimento_extra
					case _:
						huffman_codes[i] = code
						i +=1
	
		comprimentos_codigos = [0] * 1024
		for i in huffman_codes.keys():
			comprimentos_codigos[i] = huffman_codes[i]
		return comprimentos_codigos
		
	def descodifica(self, huffman_tree_HLIT, huffman_tree_HDIST):#esta função descodifica o texto e transforma em literal ou par bits a recuar/copiar
		#array com o valor inicial dos intervalos sempre que na tabela o número de bits aumenta
		niveis = [11, 19, 35, 67, 131]
		i=0
		texto = [0 for j in range(32768)]
		while True:#loop infinito até que se encontre uma folha
			bit = self.readBits(1)
			code = huffman_tree_HLIT.nextNode(str(bit))
			if code >= 0:
				huffman_tree_HLIT.resetCurNode()
				if code < 256:#se for menor que 256 é um literal
					texto[i] = code
					i += 1
							
				elif code == 256:#se for igual a 256 chegou ao fim
					break

				else:#se for maior que 256 temos de calcular a distancia a recuar
					if code == 285:
						lenght = 258
					elif 257 <= code <= 264:
						lenght = code - 254
						#por observação da tabela
					else:
						bits = (( code - 265 ) // 4) + 1
						lenght = niveis[bits - 1] + (2 ** bits) * (( code - 265 ) % 4) + self.readBits(bits)
						# niveis[bits - 1]: o primeiro valor do intervalo quando o número de bits a ler aumenta
						# (2 ** bits) * (( code - 265 ) % 4) : intervalo de valores da distancia consoante o número de bits
						#(intervalo correspondente ao numero de combinaçoes que se pode fazer como o numero de bits)
						# self.readBits(bits) : escolhe o número dentro do intervalo
					
					dist = self.distancia(huffman_tree_HDIST)#chama a função para calcular a distancia
					recua = i - dist #calcula o primeiro caracter a copiar
					for k in range(lenght):#copia os caracteres
						
						texto[i] = texto[recua]
						recua += 1
						i += 1
		return texto[0:i] #devolve o texto
	
	def distancia(self, huffman_tree_HDIST):#esta função calcula o valor da distancia a recuar
		#array com o valor inicial dos intervalos sempre que na tabela o número de bits aumenta
		niveis = [5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385]
		while True: #loop infinito até que se encontre uma folha
			bit = self.readBits(1) #ler um bit 
			code = huffman_tree_HDIST.nextNode(str(bit)) #descer na arvore 
			if code >= 0:
				huffman_tree_HDIST.resetCurNode()
				if code <= 3:
					#se o codigo for entre 0 e 3, a distancia a recuar é igual ao código +1
					distancia = code + 1
				else:
					#se o valor obtido for maior que 4 sera calculada a distancia a recuar seguindo a tabela
					bits = ((code - 4) // 2) + 1 #calcula o valor de bits extra atraves do codigo lido
					#porque os bits a ler aumentam de dois em dois na tabela
					distancia = niveis[bits - 1] + (2 ** bits) * (code % 2) + self.readBits(bits) 
					# niveis[bits - 1]: o primeiro valor do intervalo quando o número de bits a ler aumenta
					# (2 ** bits) * (code % 2) : intervalo de valores da distancia consoante o número de bits
					#(intervalo correspondente ao numero de combinaçoes que se pode fazer como o numero de bits)
					# self.readBits(bits) : escolhe o número dentro do intervalo
				return distancia # retorna o valor da distancia a recuar

	
	def escreveFicheiro(self, texto): #funcao para escrever os dados descompactados em binário
		ficheiro = open(self.gzh.fName, "wb")
		ficheiro.write(bytes(texto))
		ficheiro.close()
	
#------------------------------------Fim do nosso codigo --------------------------------





	def getOrigFileSize(self):
		''' reads file size of original file (before compression) - ISIZE '''
		
		# saves current position of file pointer
		fp = self.f.tell()
		
		# jumps to end-4 position
		self.f.seek(self.fileSize-4)
		
		# reads the last 4 bytes (LITTLE ENDIAN)
		sz = 0
		for i in range(4): 
			sz += self.f.read(1)[0] << (8*i)
		
		# restores file pointer to its original position
		self.f.seek(fp)
		
		return sz		
	

	
	def getHeader(self):  
		''' reads GZIP header'''

		self.gzh = GZIPHeader()
		header_error = self.gzh.read(self.f)
		return header_error
		

	def readBits(self, n, keep=False):
		''' reads n bits from bits_buffer. if keep = True, leaves bits in the buffer for future accesses '''

		while n > self.available_bits:
			self.bits_buffer = self.f.read(1)[0] << self.available_bits | self.bits_buffer
			self.available_bits += 8
		
		mask = (2**n)-1
		value = self.bits_buffer & mask

		if not keep:
			self.bits_buffer >>= n
			self.available_bits -= n

		return value

if __name__ == '__main__':

	# gets filename from command line if provided
	filename = "C:/Users/diogo/OneDrive/Documentos/Ficheiros/DEI/2_ANO/TI/Trabalho2/TP2 - Deflate/base code - python/FAQ.txt.gz"
	if len(sys.argv) > 1:
		filename = sys.argv[1]			

	# decompress file
	gz = GZIP(filename)
	gz.decompress()