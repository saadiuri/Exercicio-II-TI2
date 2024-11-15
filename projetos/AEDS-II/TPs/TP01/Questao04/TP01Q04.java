// package Questao04;

import java.util.Random;
import java.util.Scanner;

public class TP01Q04 {

    private static boolean isFim(String s) {
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }

    private static String alteracaoAleatoria(String s) {
        // Converte string para um array de caracteres para facilitar a manipulação
        char[] textoArray = s.toCharArray();

        // Gerador de letras aleatorias
        Random gerador = new Random();
        gerador.setSeed(4);
        char LetraInicial = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
        char LetraFinal = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));

        // Iteração sobre o array de caracteres
        for (int i = 0; i < textoArray.length; i++) {
            // Troca o caracter velho pelo novo
            if (textoArray[i] == LetraInicial) {
                textoArray[i] = LetraFinal;
            }
        }

        // Converte o array de volta para uma String e retorna
        return new String(textoArray);
    }

    private static void Resultado() {
        try (Scanner sc = new Scanner(System.in)) {
            String texto = sc.nextLine();

            while (!isFim(texto)) {
                texto = alteracaoAleatoria(texto); // Atualiza a variável texto
                System.out.println(texto); // Imprime o resultado da substituição
                texto = sc.nextLine();
            }
        }
    }

    public static void main(String[] args) {
        Resultado();
    }
}
