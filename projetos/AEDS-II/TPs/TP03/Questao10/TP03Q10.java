
import java.io.File;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Pokemon {

    private String id;
    private int generation;
    private String name;
    private String description;
    private String type1;
    private String type2;
    private String abilities;
    private double weightKg;
    private double heightM;
    private int captureRate;
    private boolean isLegendary;
    private LocalDate captureDate;

    public Pokemon() {
    }

    public Pokemon(String csvLine) {
        String[] values = csvLine.split(";");
        setId(values[0]);
        setGeneration(Integer.parseInt(values[1]));
        setName(values[2]);
        setDescription(values[3]);
        setType1(values[4]);
        setType2(values[5]);
        setAbilities(values[6]);
        setWeightKg(Double.parseDouble(values[7]));
        setHeightM(Double.parseDouble(values[8]));
        setCaptureRate(Integer.parseInt(values[9]));
        setLegendary(values[10]);
        setCaptureDate(LocalDate.parse(values[11]));
    }

    // Getters and Setters
    public String getId() {
        return id;
    }

    public void setId(String id) {
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

    public String getType1() {
        return type1;
    }

    public void setType1(String type1) {
        this.type1 = type1;
    }

    public String getType2() {
        return type2;
    }

    public void setType2(String type2) {
        this.type2 = type2;
    }

    public String getAbilities() {
        return abilities;
    }

    public void setAbilities(String abilities) {
        this.abilities = abilities;
    }

    public double getWeightKg() {
        return weightKg;
    }

    public void setWeightKg(double weightKg) {
        this.weightKg = weightKg;
    }

    public double getHeightM() {
        return heightM;
    }

    public void setHeightM(double heightM) {
        this.heightM = heightM;
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

    public void setLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    public void setLegendary(String isLegendary) {
        this.isLegendary = isLegendary.equalsIgnoreCase("TRUE");
    }

    public LocalDate getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(LocalDate captureDate) {
        this.captureDate = captureDate;
    }

    @Override
    public String toString() {
        return "[" + getId() + " ## " + getGeneration() + " ## " + getName() + " ## " + getDescription()
                + " ## " + getType1() + " ## " + getType2() + " ## " + getAbilities() + " ## Weight: " + getWeightKg()
                + "kg ## Height: " + getHeightM() + "m ## Capture Rate: " + getCaptureRate() + " ## Legendary: " + isLegendary()
                + " ## Capture Date: " + getCaptureDate() + "]";
    }

    public int compareTo(Pokemon p) {
        int generationDiff = Integer.compare(this.getGeneration(), p.getGeneration());
        return (generationDiff != 0) ? generationDiff : this.getName().compareTo(p.getName());
    }
}

class Celula {

    Pokemon pokemon;
    Celula next;

    public Celula(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.next = null;
    }
}

class Lista {

    private Celula primeiro;
    private Celula ultimo;

    public Lista() {
        primeiro = null;
        ultimo = null;
    }

    public void inserirFim(Pokemon pokemon) {
        Celula nova = new Celula(pokemon);
        if (primeiro == null) {
            primeiro = ultimo = nova;
        } else {
            ultimo.next = nova;
            ultimo = nova;
        }
    }

    private Celula partition(Celula low, Celula high) {
        Pokemon pivot = high.pokemon;
        Celula i = low;
        Celula j = low;
        Celula prev = low;

        while (j != high) {
            if (j.pokemon.compareTo(pivot) <= 0) {
                Pokemon temp = i.pokemon;
                i.pokemon = j.pokemon;
                j.pokemon = temp;
                prev = i;
                i = i.next;
            }
            j = j.next;
        }

        Pokemon temp = i.pokemon;
        i.pokemon = high.pokemon;
        high.pokemon = temp;

        return prev;
    }

    private void quickSortRec(Celula low, Celula high) {
        if (low != high && high != null && low != high.next) {
            Celula pi = partition(low, high);
            quickSortRec(low, pi);
            quickSortRec(pi.next, high);
        }
    }

    public void quickSort() {
        if (primeiro != null) {
            quickSortRec(primeiro, ultimo);
        }
    }

    public void imprimir() {
        Celula current = primeiro;
        while (current != null) {
            System.out.println(current.pokemon);
            current = current.next;
        }
    }
}

public class TP03Q10 {

    private static List<Pokemon> pokemons = new ArrayList<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void readFile(String path) {
        try (Scanner fileScanner = new Scanner(new File(path))) {
            fileScanner.nextLine(); // skip header
            while (fileScanner.hasNextLine()) {
                pokemons.add(new Pokemon(fileScanner.nextLine()));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Pokemon findPokemon(String id) {
        for (Pokemon pokemon : pokemons) {
            if (pokemon.getId().equals(id)) {
                return pokemon;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        readFile("/tmp/pokemon.csv");
        Lista pokemonLista = new Lista();

        String id = scanner.nextLine();
        while (!id.equals("FIM")) {
            Pokemon pokemon = findPokemon(id);
            if (pokemon != null) {
                pokemonLista.inserirFim(pokemon);
            }
            id = scanner.nextLine();
        }

        pokemonLista.quickSort();
        pokemonLista.imprimir();

        scanner.close();
    }
}
