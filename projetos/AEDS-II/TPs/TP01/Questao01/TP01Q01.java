// package Questao01;

import java.util.Scanner;

public class TP01Q01 {
    private static Boolean isPalindromo(String texto) {
        int tam = texto.length() - 1;

        char[] textoArray = texto.toCharArray();

        boolean IS_Palindromo = true; // Para não encher o código de return

        for (int i = 0; i <= tam; i++) {
            if (textoArray[i] != textoArray[tam - i])
                IS_Palindromo = false;
        }

        return IS_Palindromo;
    }

    private static boolean isFim(String s) {
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }

    private static void Resultado() {
        try (Scanner sc = new Scanner(System.in)) {
            String texto = sc.nextLine();

            while (!isFim(texto)) {
                if (isPalindromo(texto))
                    System.out.println("SIM");
                else
                    System.out.println("NAO");
                texto = sc.nextLine();
            }
        }
    }

    public static void main(String[] args) {
        Resultado();
    }
}
