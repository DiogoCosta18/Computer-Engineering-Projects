import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Arquivo {
    Arquivo(){}
    public List<Pergunta> lerPerguntas(String arquivo) {
        // ler do ficheiro
        List<Pergunta> perguntas = new ArrayList<>();
        try{
            File f= new File(arquivo);
            FileReader fr = new FileReader(f);
            BufferedReader br= new BufferedReader(fr);

            String linha;
            while ((linha = br.readLine()) != null) {
                String[] partes = linha.split(";");
                

                String tipo = partes[0];
                switch (tipo) {
                    case "Artes":
                        perguntas.add(new Artes().lePergunta(partes));
                        break;
                    case "Futebol":
                        perguntas.add(new Futebol().lePergunta(partes));
                        break;
                    case "Ski":
                        perguntas.add(new Ski().lePergunta(partes));
                        break;
                    case "Natacao":
                        perguntas.add(new Natacao().lePergunta(partes));
                        break;
                    case "Ciencias":
                        perguntas.add(new Ciencias().lePergunta(partes));
                        break;
                    default:
                        System.out.println("Tipo de pergunta desconhecido: " + tipo);  
                }
                //System.out.println(pergunta.toString());
            }
        br.close();
        }catch(FileNotFoundException e){
            System.out.println("Ficheiro nao encontrado");
        }catch(IOException e){
            System.out.println("Erro ao ler o ficheiro");
        }
        return perguntas;
    }

    public void salvarJogo(Jogo jogo, String nomeArquivo) {
        //guardar num ficheiro
    }

    public Jogo carregarJogo(String nomeArquivo) {
        // carregar os dados de um ficheiro
    }
}

