// package Questao03;

import java.util.Scanner;

public class TP01Q03 {
    private static String CiframentoDeCesar(String texto) {
        int tam = texto.length() - 1;

        char[] textoArray = texto.toCharArray();

        for (int i = 0; i <= tam; i++) {
            if (texto.charAt(i) >= 0 && texto.charAt(i) <= 127) // verifica se não é char especial
                textoArray[i] += 3;
            /*
             * else
             * textoArray[i] = textoArray[i];
             */
        }

        return String.copyValueOf(textoArray);
    }

    private static boolean isFim(String s) {
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }

    private static void Resultado() {
        try (Scanner sc = new Scanner(System.in)) {
            String texto;

            texto = sc.nextLine();

            while (!isFim(texto)) {
                System.out.println(CiframentoDeCesar(texto));

                texto = sc.nextLine();
            }
        }
    }

    public static void main(String[] args) {
        Resultado();
    }
}
