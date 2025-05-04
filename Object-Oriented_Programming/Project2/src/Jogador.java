import java.io.Serializable;

public class Jogador implements Serializable{
    private String nome;

    public Jogador(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public String getNomeFormatado() {
        String[] iniciais = nome.split(" ");
        String getNomeFormatado = "";
        for (int i = 0; i < iniciais.length; i++) {
            getNomeFormatado += iniciais[i].charAt(0);
        }
        return getNomeFormatado;
    }
}
