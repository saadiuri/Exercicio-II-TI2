// package Questao12;

import java.util.Scanner;

public class TP01Q12 {

    // Função recursiva para realizar o Ciframento de César
    private static String CiframentoDeCesarRecursivo(char[] textoArray, int i) {
        if (i < textoArray.length) {
            // Verifica se o caractere está no intervalo ASCII padrão
            if (textoArray[i] >= 0 && textoArray[i] <= 127) {
                textoArray[i] += 3; // Aplica o deslocamento de César
            }
            // Chamada recursiva para o próximo caractere
            CiframentoDeCesarRecursivo(textoArray, i + 1);
        }

        // Retorna a string após o ciframento recursivo
        return String.copyValueOf(textoArray);
    }

    // Função auxiliar que inicia o processo de ciframento
    private static String CiframentoDeCesar(String texto) {
        char[] textoArray = texto.toCharArray(); // Converte a string para um array de caracteres
        String resultado = CiframentoDeCesarRecursivo(textoArray, 0); // Inicia a recursão
        return resultado;
    }

    // Função para verificar se a entrada é "FIM"
    private static boolean isFim(String s) {
        boolean resultado = (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
        return resultado;
    }

    // Função principal para processamento do texto
    private static void Resultado() {
        try (Scanner sc = new Scanner(System.in)) {
            String texto = sc.nextLine(); // Leitura inicial

            while (!isFim(texto)) { // Continua até receber "FIM"
                System.out.println(CiframentoDeCesar(texto)); // Imprime o resultado do ciframento
                texto = sc.nextLine(); // Leitura do próximo texto
            }
        }
    }

    public static void main(String[] args) {
        Resultado(); // Chamada da função principal
    }
}
