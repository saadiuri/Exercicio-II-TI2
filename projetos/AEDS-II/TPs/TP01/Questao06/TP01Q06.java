// package Questao06;

import java.util.Scanner;

public class TP01Q06 {
    
    private static boolean SomenteConsoante(String s) {
        // Para não encher o código de return
        boolean soConsoantes = true;
        // Definindo um array de consoantes
        String consoantes = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

        for (int i = 0; i < s.length(); i++) {
            if (!consoantes.contains(String.valueOf(s.charAt(i)))) {
                soConsoantes = false;
                i = s.length(); // Se encontrar um caractere que não é consoante, pode sair
            }
        }
        return soConsoantes;
    }

    private static boolean SomenteVogal(String s) {
        boolean soVogais = true;
        // Definindo um array de vogais
        String vogais = "aeiouAEIOU";

        for (int i = 0; i < s.length(); i++) {
            if (!vogais.contains(String.valueOf(s.charAt(i)))) {
                soVogais = false;
                i = s.length(); // Se encontrar um caractere que não é vogal, pode sair
            }
        }
        return soVogais;
    }

    private static boolean SomenteInteiro(String s) {
        boolean soInteiro = true;
        // Verifica se a string esta vazia
        if (s.isEmpty()) {
            soInteiro = false;
        }

        int startIndex = 0;
        if (s.charAt(0) == '-') { // Verificar se há um sinal de negativo
            if (s.length() == 1) {
                soInteiro = false; // Apenas um sinal de negativo não é um número inteiro
            }
            startIndex = 1;
        }

        for (int i = startIndex; i < s.length(); i++) {
            if (!Character.isDigit(s.charAt(i))) {
                soInteiro = false; // Se encontrar um caractere que não é dígito, retorna falso
            }
        }
        return soInteiro;
    }

    private static boolean SomenteReal(String s) {
        boolean soReal = true;
        // Verifica se a string esta vazia
        if (s.isEmpty()) {
            soReal = false;
        }

        int startIndex = 0;
        boolean pontoEncontrado = false;

        if (s.charAt(0) == '-') {
            if (s.length() == 1) {
                soReal = false;
            }
            startIndex = 1;
        }

        for (int i = startIndex; i < s.length(); i++) {
            char currentChar = s.charAt(i);

            if (currentChar == '.') {
                if (pontoEncontrado) {
                    soReal = false; // Segundo ponto encontrado, não é um número real válido
                }
                pontoEncontrado = true;
            } else if (!Character.isDigit(currentChar)) {
                soReal = false; // Caracter que não é dígito nem ponto, não é um número real
            }
        }

        return soReal;
    }

    private static void avaliarEntrada(String s) {
        boolean x1 = SomenteVogal(s);
        boolean x2 = SomenteConsoante(s);
        boolean x3 = SomenteInteiro(s);
        boolean x4 = SomenteReal(s);

        // Formata a saída conforme o solicitado
        String resultado = (x1 ? "SIM" : "NAO") + " " +
                (x2 ? "SIM" : "NAO") + " " +
                (x3 ? "SIM" : "NAO") + " " +
                (x4 ? "SIM" : "NAO");

        System.out.println(resultado);
    }

    private static void Resultado() {
        try (Scanner sc = new Scanner(System.in)) {

            while (sc.hasNextLine()) {
                String linha = sc.nextLine().trim();
                if (!linha.isEmpty()) { // Verifica se a linha não está vazia
                    avaliarEntrada(linha);
                }
            }

            sc.close();
        }
    }

    public static void main(String[] args) {
        Resultado();
    }
}