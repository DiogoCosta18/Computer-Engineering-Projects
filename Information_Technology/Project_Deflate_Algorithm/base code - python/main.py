# Author: Marco Simoes
# Adapted from Java's implementation of Rui Pedro Paiva
# Teoria da Informacao, LEI, 2022

import sys
from huffmantree import HuffmanTree
from collections import Counter


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
    fComment = ''  # ends when a byte with value 0 is read

    # if FLG_HCRC == 1
    HCRC = []

    def read(self, f):
        ''' reads and processes the Huffman header from file. Returns 0 if no error, -1 otherwise '''

        # ID 1 and 2: fixed values
        self.ID1 = f.read(1)[0]
        if self.ID1 != 0x1f: return -1  # error in the header

        self.ID2 = f.read(1)[0]
        if self.ID2 != 0x8b: return -1  # error in the header

        # CM - Compression Method: must be the value 8 for deflate
        self.CM = f.read(1)[0]
        if self.CM != 0x08: return -1  # error in the header

        # Flags
        self.FLG = f.read(1)[0]

        # MTIME
        self.MTIME = [0] * self.lenMTIME
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
            self.XLEN = [0] * self.lenXLEN
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
        self.f.seek(0, 2)
        self.fileSize = self.f.tell()
        self.f.seek(0)

    #funcao que le e devolve os valores de HLIT, HDIST, HCLEN da stream
    def Ex1(self):
        HLIT = self.readBits(5) + 257   #le 5 bits e soma-se 257
        HDIST = self.readBits(5) + 1    #le 5 bits e soma-se 1
        HCLEN = self.readBits(4) + 4    #le 4 bits e soma-se 4

        print("HLIT: ", HLIT)
        print("HDIST: ", HDIST)
        print("HCLEN: ", HCLEN)
        return HLIT, HDIST, HCLEN

    # funcao que le os bits relativos ao comprimento do codigo de cada simbolo
    # guarda cada simbolo com o respetivo comprimento do seu codigo no array compCodigos
    def Ex2(self, HCLEN):
        compCodigos = [0 for i in range(19)]
        ordemCodigos = [16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15]

        for i in range(HCLEN):
            compCodigos[ordemCodigos[i]] = self.readBits(3)
        return compCodigos

    # funcao que, dado um array de comprimentos, gera os codigos de Huffman correspondentes e constroi a respetiva arvore de Huffman
    def Ex3(self, compCodigos):
        hft = HuffmanTree()

        counts = Counter(compCodigos)
        bl_count = [counts[key] if key in counts.keys() else 0 for key in range(max(compCodigos) + 1)] #armazena a contagem de cada símbolo
        codigos = [-1 for i in range(len(compCodigos))]  # vai armazenar o codigo huffman de cada um dos simbolos
        next_code = [0 for i in range(len(bl_count))] # armazena o próximo código disponível para cada comprimento de código

        code = 0
        bl_count[0] = 0 # Atribui a contagem de simbolos com comprimento 0 a 0 uma vez que estes simbolos nao existem
        for bits in range(1, len(bl_count)):
            code = (code + bl_count[bits - 1]) << 1 # Calcula o proximo codigo disponivel realizando um shift a esquerda sobre o codigo anterior de 1 bit
            next_code[bits] = code # guarda o codigo calculado anteriormente na lista next_code

        for n in range(len(compCodigos)):
            lenght = compCodigos[n]
            if (lenght != 0):
                codigos[n] = next_code[lenght] # Atribui o proximo codigo disponivel
                str_aux = (bin(codigos[n]).replace("0b", "")).zfill(lenght) #converte o codigo para uma string de 0s e 1s, sendo adicionados 0s a esquerda para assegurar o comprimento correto de cada codigo
                hft.addNode(str_aux, n, False) # Adiciona o no a Huffman tree
                next_code[lenght] += 1 # Incrementa o proximo codigo disponivel para o comprimento atual

        print("\n(simbolo, compCodigo, codigo): ", *[(i, compCodigos[i], bin(codigos[i]).replace("0b", "").zfill(compCodigos[i])) if codigos[i] != -1 else (i, compCodigos[i], '-')
            for i in range(len(compCodigos))], sep='\n')
        return codigos, hft


    # função que le e armazena num array os comprimentos dos codigos (Comp_H) referentes ao alfabeto
    # de literais/comprimentos, codificados segundo o codigo de Huffman de comprimentos de codigos
    def Ex4(self, hft, Comp_H):
        # H_Lens e um array com todos os indices a 0 com espaco para armazenar Comp_H valores
        H_Lens = [0 for i in range(Comp_H)]

        i = 0
        hft.resetCurNode()  # reposiciona o ponteiro curNode na raiz da arvore
        while (i < Comp_H):

            aux = format("%d" % self.readBits(1))
            aux = hft.nextNode(aux)

            # nextNode e uma funcao de pesquisa bit a bit que atualiza o no corrente na arvore
            # com base no no atual (curNode da arvore hft) e o bit seguinte.
            # devolve -1 se nao encontrou o no, -2 se encontrou mas nao e folha e o indice no alfabeto se e folha

            if aux == -2:
                continue
            elif aux >= 0:
                if aux == 16:
                    repeat = self.readBits(2) + 3
                    for j in range(repeat):
                        H_Lens[i] = H_Lens[i - 1]   # copia o comprimento de codigo entre 3 a 6 vezes
                        i += 1
                elif aux == 17:
                    repeat = self.readBits(3) + 3
                    for j in range(repeat):
                        H_Lens[i] = 0   # deixa o indice i do array H_Lens nulo entre 3 a 10 vezes
                        i += 1
                elif aux == 18:
                    repeat = self.readBits(7) + 11
                    for j in range(repeat):
                        H_Lens[i] = 0   # deixa o indice i do array H_Lens nulo entre 11 e 138 vezes
                        i += 1
                else:
                    H_Lens[i] = aux # representa o comprimento do codigo diretamente
                    i += 1
                hft.resetCurNode()
            elif aux == -1:
                pass  # not found

        # O alfabeto do comprimento dos códigos, H_Lens, fica totalmente preenchido
        # quando tiverem sido percorridos todos os Comp_H índices

        # Chama-se a funcao Ex3 para que as arvores HLIT_Tree e HDIST_Tree sejam realizadas
        H_cods, H_Tree = self.Ex3(H_Lens)
        print("\nsuper BALLS", H_cods, H_Tree)
        return H_cods, H_Tree

    # esta funcao le bit a bit da stream e percorre a arvore das distancias (hft_HDIST)
    # consoante o valor obtido na folha da arvore, sera calculado o valor da distancia a recuar
    # para quando um valor for obtido
    # retorna o valor da distancia (bytes) a recuar
    def Distancia(self, hft_HDIST):
        # array com o valor inicial dos intervalos correspondentes ao numero de bits extra a ler para obter a dist (de 1 a 13 bits)
        offset_dist = [5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385]
        hft_HDIST.resetCurNode()
        while (True):
            aux_dist = format("%d" % self.readBits(1))

            aux_dist = hft_HDIST.nextNode(aux_dist)

            if aux_dist == -2:
                continue
            elif aux_dist == -1:
                pass  # not found
            elif 0 <= aux_dist <= 28:
                if 0 <= aux_dist <= 3:  # o valor da dist e a soma do valor o obtido na folha da arvore com 1
                    dist = aux_dist + 1
                else:
                    # se o valor obtido for entre 4 e 18  sera calculada uma dist (numero de bytes a recuar) de acordo com a tabela de dist do Deflate
                    bits = ((aux_dist - 4) // 2) + 1
                    dist = offset_dist[bits - 1] + (2 ** bits) * (aux_dist % 2) + self.readBits(bits)
                break
        return dist

    #funcao que realiza a descompactacao dos dados comprimidos (gzip), com base nos códigos de Huffman e no algoritmo LZ77
    def Ex7(self, hft_HLIT, hft_HDIST):

        #array com o valor inicial dos intervalos correspondentes ao numero de bits extra a ler para obter a lenght (de 1 a 5 bits)
        offset = [11, 19, 35, 67, 131]

        #array que ira conter os dados descompactados
        output_buffer = [-1 for i in range(32768)]

        hft_HLIT.resetCurNode()

        #indice do output_buffer onde sera adicionado o proximo dados descomprimido
        indice=0

        #ciclo para ler bit a bit da stream e percorrer a arvore dos literais (hft_HLIT)
        #consoante o valor obtido na folha da arvore, sera adicionado o valor adequado ao output_buffer
        #para quando o valor 256 for obtido
        while(True):

            aux = format("%d" % self.readBits(1))
            aux = hft_HLIT.nextNode(aux)

            if aux == -2:
                continue
            elif aux == -1:
                #reset
                hft_HLIT.resetCurNode()
                pass  # not found
            elif aux == 256:
                break # final
            else:
                hft_HLIT.resetCurNode()
                if 0 <= aux < 256: #adiciona o valor obtido diretamente da arvore hft_HLIT ao out_buffer
                    output_buffer[indice] = aux
                    indice+=1
                else:
                    #se o valor obtido for superior a 256 sera calculada uma length (numero de bytes a copiar) de acordo com a tabela de length do Deflate
                    #de seguida sera calculada a distancia a recuar com recurso a funcao Distancia
                    lenght=0
                    if 257 <= aux <= 264:
                        lenght = aux-254
                    elif aux == 285:
                        lenght = 258
                    elif 265 <= aux <= 284:
                        bits = ((aux-265)//4) + 1
                        # lenght = aux - offset[bits-1] + (2**bits - 1) + self.readBits(bits)
                        lenght = offset[bits - 1] + (2 ** bits) * ((aux - 265) % 4) + self.readBits(bits)
                    dist = self.Distancia(hft_HDIST)
                    #recua - indice do output_buffer a partir do qual serao copiados length bytes
                    recua = indice - dist
                    for i in range(lenght):
                        output_buffer[indice] = output_buffer[recua]
                        recua += 1
                        indice += 1


        print(output_buffer[0:indice])
        return output_buffer[0:indice]




    #funcao que guarda os dados descompactados num ficheiro binario
    def Ex8(self, output_buffer):
        #binario
        # binary_file = open("abcBIN", "wb")
        binary_file = open(self.gzh.fName, "wb")
        binary_file.write(bytes(output_buffer))
        binary_file.close()



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
                print('Error: Block %d not coded with Huffman Dynamic coding' % (numBlocks + 1))

                return

            # --- STUDENTS --- ADD CODE HERE
            #

            HLIT, HDIST, HCLEN = self.Ex1() #Ex1
            compCodigos = self.Ex2(HCLEN) #Ex2
            codigos, hft = self.Ex3(compCodigos) #Ex3
            HLIT_cods, HLIT_Tree = self.Ex4(hft, HLIT) #Ex5
            HDIST_cods, HDIST_Tree = self.Ex4(hft, HDIST) #Ex6
            print(HDIST_cods)
            print(HLIT_cods)
            output_buffer = self.Ex7(HLIT_Tree, HDIST_Tree) #Ex7
            self.Ex8(output_buffer) #Ex8

            # update number of blocks read
            numBlocks += 1

        # close file

        self.f.close()
        print("End: %d block(s) analyzed." % numBlocks)

    def getOrigFileSize(self):
        ''' reads file size of original file (before compression) - ISIZE '''

        # saves current position of file pointer
        fp = self.f.tell()

        # jumps to end-4 position
        self.f.seek(self.fileSize - 4)

        # reads the last 4 bytes (LITTLE ENDIAN)
        sz = 0
        for i in range(4):
            sz += self.f.read(1)[0] << (8 * i)

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

        mask = (2 ** n) - 1
        value = self.bits_buffer & mask

        if not keep:
            self.bits_buffer >>= n
            self.available_bits -= n

        return value


if __name__ == '__main__':

    # gets filename from command line if provided
    filename = "C:/Users/diogo/OneDrive/Documentos/Ficheiros/DEI/2_ANO/TI/Trabalho2/TP2 - Deflate/base code - python/FAQ.txt.gz"
    if len(sys.argv) > 1:
        fileName = sys.argv[1]

        # decompress file
    gz = GZIP(filename)
    gz.decompress()
