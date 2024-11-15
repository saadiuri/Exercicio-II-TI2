//package TP02.Questao01;

// TP02Q01.java
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

// Classe Pokemon
class Pokemon implements Cloneable {
    private int id;
    private int generation;
    private String name;
    private String description;
    private List<String> types;
    private List<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    // Construtores
    public Pokemon() {
        this.id = 0;
        this.generation = 0;
        this.name = "";
        this.description = "";
        this.types = new ArrayList<>();
        this.abilities = new ArrayList<>();
        this.weight = 0.0;
        this.height = 0.0;
        this.captureRate = 0;
        this.isLegendary = false;
        this.captureDate = new Date(); // Data atual por padrão
    }

    public Pokemon(int id, int generation, String name, String description, List<String> types,
            List<String> abilities, double weight, double height, int captureRate, boolean isLegendary,
            Date captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    // Getters e Setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getGeneration() {
        return generation;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public List<String> getTypes() {
        return types;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }

    public List<String> getAbilities() {
        return abilities;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public int getCaptureRate() {
        return captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    public boolean isLegendary() {
        return isLegendary;
    }

    public void setLegendary(boolean legendary) {
        isLegendary = legendary;
    }

    public Date getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

    // Método imprimir
    public void imprimir() {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        String captureDateStr = (captureDate != null) ? sdf.format(captureDate) : "N/A";

        // Formatar tipos e habilidades para ficarem no formato ['tipo1', 'tipo2']
        String formattedTypes = formatList(types);
        String formattedAbilities = formatList(abilities);

        System.out.printf("[#%d -> %s: %s - %s - %s - %.1fkg - %.1fm - %d%% - %b - %d gen] - %s\n",
                id, name, description, formattedTypes, formattedAbilities, weight, height, captureRate, isLegendary,
                generation,
                captureDateStr);
    }

    // Método auxiliar para formatar listas
    private String formatList(List<String> list) {
        if (list.isEmpty()) {
            return "[]";
        }
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < list.size(); i++) {
            sb.append("'");
            sb.append(list.get(i));
            sb.append("'");
            if (i < list.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }

    // Método ler para processar uma linha CSV usando campos já divididos
    public void ler(String[] campos) {
        // Tratar e atribuir cada campo, substituindo valores ausentes por padrão
        try {
            // id
            this.id = campos[0].isEmpty() ? 0 : Integer.parseInt(campos[0].trim());

            // generation
            this.generation = campos[1].isEmpty() ? 0 : Integer.parseInt(campos[1].trim());

            // name
            this.name = campos[2].isEmpty() ? "" : campos[2].trim();

            // description
            this.description = campos[3].isEmpty() ? "" : campos[3].trim();

            // types: type1 e type2
            this.types = new ArrayList<>();
            if (!campos[4].isEmpty()) {
                this.types.add(campos[4].trim());
            }
            if (!campos[5].isEmpty()) {
                this.types.add(campos[5].trim());
            }

            // abilities
            this.abilities = new ArrayList<>();
            if (!campos[6].isEmpty()) {
                // Remover [ ], ' e " e espaços
                String habilidades = campos[6].replaceAll("[\\[\\]\"']", "").trim();
                // Dividir por vírgula
                String[] habilidadesArray = habilidades.split(",");
                for (String habilidade : habilidadesArray) {
                    if (!habilidade.isEmpty()) {
                        this.abilities.add(habilidade.trim());
                    }
                }
            }

            // weight_kg
            try {
                this.weight = campos[7].isEmpty() ? 0.0 : Double.parseDouble(campos[7].trim());
            } catch (NumberFormatException e) {
                this.weight = 0.0;
            }

            // height_m
            try {
                this.height = campos[8].isEmpty() ? 0.0 : Double.parseDouble(campos[8].trim());
            } catch (NumberFormatException e) {
                this.height = 0.0;
            }

            // capture_rate
            try {
                this.captureRate = campos[9].isEmpty() ? 0 : Integer.parseInt(campos[9].trim());
            } catch (NumberFormatException e) {
                this.captureRate = 0;
            }

            // is_legendary
            this.isLegendary = campos[10].isEmpty() ? false : campos[10].trim().equals("1");

            // capture_date
            if (!campos[11].isEmpty()) {
                SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
                try {
                    this.captureDate = sdf.parse(campos[11].trim());
                } catch (ParseException e) {
                    this.captureDate = null; // Data inválida, definida como null
                }
            } else {
                this.captureDate = null; // Data ausente
            }

        } catch (Exception e) {
            System.err.println("Erro ao ler Pokémon: " + e.getMessage());
            // Atribuir valores padrão em caso de erro
            this.id = 0;
            this.generation = 0;
            this.name = "";
            this.description = "";
            this.types = new ArrayList<>();
            this.abilities = new ArrayList<>();
            this.weight = 0.0;
            this.height = 0.0;
            this.captureRate = 0;
            this.isLegendary = false;
            this.captureDate = null;
        }
    }

    // Método clone
    @Override
    public Pokemon clone() {
        try {
            Pokemon clone = (Pokemon) super.clone();
            clone.types = new ArrayList<>(this.types);
            clone.abilities = new ArrayList<>(this.abilities);
            clone.captureDate = (this.captureDate != null) ? (Date) this.captureDate.clone() : null;
            return clone;
        } catch (CloneNotSupportedException e) {
            throw new RuntimeException(e);
        }
    }
}

// Classe principal
public class TP02Q01 {

    public static void main(String[] args) {
        List<Pokemon> pokemons = new ArrayList<>();

        String caminhoArquivo = "pokemon.csv"; // Ajuste o caminho conforme necessário

        // Leitura do arquivo CSV
        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
            String linha;
            boolean primeiraLinha = true; // Para ignorar o cabeçalho

            while ((linha = br.readLine()) != null) {
                if (primeiraLinha) {
                    primeiraLinha = false;
                    continue; // Ignora o cabeçalho
                }

                // Verificar se a linha contém apenas "FIM"
                if (linha.trim().equalsIgnoreCase("FIM")) {
                    break; // Controla a saída do loop sem `break`
                }

                // Dividir a linha, ignorando vírgulas dentro de aspas
                String[] campos = linha.split(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)", -1);

                // Criar objeto Pokemon
                Pokemon p = new Pokemon();
                p.ler(campos);
                pokemons.add(p);
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }

        // Leitura de IDs da entrada padrão
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine().trim();
            if (input.equalsIgnoreCase("FIM")) {
                break;
            }

            try {
                int idProcurado = Integer.parseInt(input);
                boolean encontrado = false;

                for (Pokemon p : pokemons) {
                    if (p.getId() == idProcurado) {
                        p.imprimir();
                        encontrado = true;
                        break; // Parar após encontrar
                    }
                }

                if (!encontrado) {
                    System.out.println("Pokémon com ID " + idProcurado + " não encontrado.");
                }

            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Por favor, insira um número inteiro ou 'FIM' para finalizar.");
            }
        }

        scanner.close();
    }
}
