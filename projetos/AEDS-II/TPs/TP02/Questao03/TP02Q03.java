import java.io.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

public class TP02Q03 {
    public static class Pokemon {
        private int id;
        private int generation;
        private String name;
        private String description;
        private ArrayList<String> types;
        private ArrayList<String> abilities;
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

        // Constructor that accepts a String parameter
        public Pokemon(String csvLine) {
            String[] fields = csvLine.split(",");
            this.id = Integer.parseInt(fields[0]);
            this.generation = Integer.parseInt(fields[1]);
            this.name = fields[2];
            this.description = fields[3];
            this.types = new ArrayList<>();
            for (String type : fields[4].split(";")) {
                this.types.add(type);
            }
            this.abilities = new ArrayList<>();
            for (String ability : fields[5].split(";")) {
                this.abilities.add(ability);
            }
            this.weight = Double.parseDouble(fields[6]);
            this.height = Double.parseDouble(fields[7]);
            this.captureRate = Integer.parseInt(fields[8]);
            this.isLegendary = Boolean.parseBoolean(fields[9]);
            try {
                this.captureDate = new SimpleDateFormat("dd/MM/yyyy").parse(fields[10]);
            } catch (Exception e) {
                this.captureDate = new Date();
            }
        }

        public Pokemon(int id, int generation, String name, String description, ArrayList<String> types,
                ArrayList<String> abilities, double weight, double height, int captureRate, boolean isLegendary,
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

    public ArrayList<String> getTypes() {
        return types;
    }

    public void setTypes(ArrayList<String> types) {
        this.types = types;
    }

    public ArrayList<String> getAbilities() {
        return abilities;
    }

    public void setAbilities(ArrayList<String> abilities) {
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

        System.out.printf("[#%d -> %s: %s - %s - %s - %.1fkg - %.1fm - %d%% - %b - %d gen] - %s\n",
                id, name, description, types, abilities, weight, height, captureRate, isLegendary, generation,
                captureDateStr);
    }
}

    public static void main(String[] args) {
        String csvPath = "/tmp/pokemon.csv";

        // le personagens a partir de um csv
        ArrayList<Pokemon> pokemons = new ArrayList<Pokemon>();
        try {
          Scanner scanner = new Scanner(new File(csvPath));
          scanner.nextLine(); // skip header
    
          while (scanner.hasNextLine()) {
            pokemons.add(new Pokemon(scanner.nextLine()));
          }
    
          scanner.close();
        } catch (Exception e) { }
    
        Scanner sc = new Scanner(System.in);
    
        // le id e armazena o Pokemon em uma lista
        Pokemon[] PokemonsBusca = new Pokemon[50];
        int i = 0;
        String id = sc.nextLine();
        while (!id.equals("FIM")) {
          for (Pokemon Pokemon : pokemons) {
            if (Pokemon.getId() == Integer.parseInt(id)) {
              PokemonsBusca[i++] = Pokemon;
              break;
            }
          }
    
          id = sc.nextLine();
        }
    
        // le os nomes dos personagens e verifica se está na lista na posição i
        String nome = sc.nextLine();
        while (!nome.equals("FIM")) {
          boolean achou = false;
    
          for (int j = 0; j < i; j++) {
            if (PokemonsBusca[j].getName().equals(nome)) {
              achou = true;
              break;
            }
          }
    
          if (achou)
            System.out.println("SIM");
          else
            System.out.println("NAO");
    
          nome = sc.nextLine();
        }
    
        sc.close();
      }
}
