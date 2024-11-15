// ClassPokemon/Pokemon.java
package TP02.ClassPokemon;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Pokemon implements Cloneable {
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

    // Método ler para processar uma linha CSV usando campos já divididos pelo
    // OpenCSV
    public void ler(String[] campos) {
        // Tratar e atribuir cada campo, substituindo valores ausentes por padrão
        try {
            this.id = campos[0].isEmpty() ? 0 : Integer.parseInt(campos[0].trim());
            this.generation = campos[1].isEmpty() ? 0 : Integer.parseInt(campos[1].trim());
            this.name = campos[2].isEmpty() ? "" : campos[2].trim();
            this.description = campos[3].isEmpty() ? "" : campos[3].trim();

            // Tipos: type1 e type2
            this.types = new ArrayList<>();
            if (!campos[4].isEmpty()) {
                this.types.add(campos[4].trim());
            }
            if (!campos[5].isEmpty()) {
                this.types.add(campos[5].trim());
            }

            // Habilidades: remover caracteres extras e separar por vírgula
            this.abilities = new ArrayList<>();
            if (!campos[6].isEmpty()) {
                String habilidades = campos[6].replaceAll("[\\[\\]'\"\\s]", "");
                String[] habilidadesArray = habilidades.split(",");
                for (String habilidade : habilidadesArray) {
                    if (!habilidade.isEmpty()) {
                        this.abilities.add(habilidade.trim());
                    }
                }
            }

            // Peso e altura
            try {
                this.weight = campos[7].isEmpty() ? 0.0 : Double.parseDouble(campos[7].trim());
                this.height = campos[8].isEmpty() ? 0.0 : Double.parseDouble(campos[8].trim());
            } catch (NumberFormatException e) {
                this.weight = 0.0;
                this.height = 0.0;
            }

            // CaptureRate
            try {
                this.captureRate = campos[9].isEmpty() ? 0 : Integer.parseInt(campos[9].trim());
            } catch (NumberFormatException e) {
                this.captureRate = 0;
            }

            // isLegendary
            this.isLegendary = campos[10].isEmpty() ? false : campos[10].trim().equals("1");

            // Tratamento da data
            SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
            if (!campos[11].isEmpty()) {
                try {
                    this.captureDate = sdf.parse(campos[11].trim());
                } catch (ParseException e) {
                    this.captureDate = null; // Data inválida, definida como null
                }
            } else {
                this.captureDate = null; // Data ausente
            }
        } catch (NumberFormatException e) {
            System.err.println("Erro ao converter número: " + e.getMessage());
            // Configurar campos para valores padrão ou lidar conforme necessário
        }
    }

    @Override
    public Pokemon clone() {
        try {
            Pokemon clone = (Pokemon) super.clone();
            clone.types = new ArrayList<>(this.types);
            clone.abilities = new ArrayList<>(this.abilities);
            clone.captureDate = (Date) this.captureDate.clone();
            return clone;
        } catch (CloneNotSupportedException e) {
            throw new RuntimeException(e);
        }
    }
}
