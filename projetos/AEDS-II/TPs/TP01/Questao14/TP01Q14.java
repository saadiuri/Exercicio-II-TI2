// package Questao14;

import java.util.Scanner;

public class TP01Q14 {

    private static boolean SomenteConsoante(String s, int index) {
        // Caso base: se o índice for igual ao tamanho da string, terminou a verificação
        if (index == s.length()) {
            return true;
        }

        // Definindo um array de consoantes
        String consoantes = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
        char currentChar = s.charAt(index);

        // Se não for consoante, retorna false
        if (!consoantes.contains(String.valueOf(currentChar))) {
            return false;
        }

        // Chamada recursiva para o próximo caractere
        return SomenteConsoante(s, index + 1);
    }

    private static boolean SomenteVogal(String s, int index) {
        // Caso base: se o índice for igual ao tamanho da string, terminou a verificação
        if (index == s.length()) {
            return true;
        }

        // Definindo um array de vogais
        String vogais = "aeiouAEIOU";
        char currentChar = s.charAt(index);

        // Se não for vogal, retorna false
        if (!vogais.contains(String.valueOf(currentChar))) {
            return false;
        }

        // Chamada recursiva para o próximo caractere
        return SomenteVogal(s, index + 1);
    }

    private static boolean SomenteInteiro(String s, int index, boolean isNegative) {
        // Caso base: se o índice for igual ao tamanho da string, terminou a verificação
        if (index == s.length()) {
            return index > 0; // True se a string não estiver vazia
        }

        // Se o índice inicial e o caractere atual for '-', ajusta o sinal negativo
        if (index == 0 && s.charAt(index) == '-') {
            return SomenteInteiro(s, index + 1, true);
        }

        // Verifica se todos os caracteres são dígitos
        if (!Character.isDigit(s.charAt(index))) {
            return false;
        }

        // Chamada recursiva para o próximo caractere
        return SomenteInteiro(s, index + 1, isNegative);
    }

    private static boolean SomenteReal(String s, int index, boolean pontoEncontrado, boolean isNegative) {
        // Caso base: se o índice for igual ao tamanho da string, terminou a verificação
        if (index == s.length()) {
            return index > 0; // True se a string não estiver vazia
        }

        char currentChar = s.charAt(index);

        // Se o índice inicial e o caractere atual for '-', ajusta o sinal negativo
        if (index == 0 && currentChar == '-') {
            return SomenteReal(s, index + 1, pontoEncontrado, true);
        }

        // Verifica se encontrou mais de um ponto decimal
        if (currentChar == '.') {
            if (pontoEncontrado) {
                return false;
            }
            return SomenteReal(s, index + 1, true, isNegative);
        }

        // Verifica se o caractere não é um dígito
        if (!Character.isDigit(currentChar)) {
            return false;
        }

        // Chamada recursiva para o próximo caractere
        return SomenteReal(s, index + 1, pontoEncontrado, isNegative);
    }

    private static void avaliarEntrada(String s) {
        boolean x1 = SomenteVogal(s, 0);
        boolean x2 = SomenteConsoante(s, 0);
        boolean x3 = SomenteInteiro(s, 0, false);
        boolean x4 = SomenteReal(s, 0, false, false);

        // Formata a saída conforme o solicitado
        String resultado = (x1 ? "SIM" : "NAO") + " " +
                (x2 ? "SIM" : "NAO") + " " +
                (x3 ? "SIM" : "NAO") + " " +
                (x4 ? "SIM" : "NAO");

        System.out.println(resultado);
    }

    private static void Resultado(Scanner sc) {
        if (sc.hasNextLine()) {
            String linha = sc.nextLine().trim();
            if (!linha.isEmpty()) { // Verifica se a linha não está vazia
                avaliarEntrada(linha);
            }
            Resultado(sc); // Chamada recursiva para a próxima linha
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Resultado(sc);
        sc.close();
    }
}
