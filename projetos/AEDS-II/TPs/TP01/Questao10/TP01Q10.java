// package Questao10;

import java.util.Scanner;

public class TP01Q10 {

  // Método recursivo para verificar se uma string é um palíndromo
  private static Boolean palindromo(String texto, int i) {
    Boolean resultadoPalindromo; // Variável que armazena o resultado da verificação

    // Caso base: Se o índice i for igual ao comprimento da string, significa que
    // percorremos toda a string
    if (texto.length() == i) {
      resultadoPalindromo = true; // A string é um palíndromo
    }
    // Caso em que o caractere atual não corresponde ao caractere oposto (do fim
    // para o início)
    else if (texto.charAt(i) != texto.charAt(texto.length() - 1 - i)) {
      resultadoPalindromo = false; // A string não é um palíndromo
    }
    // Caso recursivo: avançar para o próximo par de caracteres
    else {
      resultadoPalindromo = palindromo(texto, ++i);
    }

    return resultadoPalindromo; // Retorna o resultado da verificação
  }

  // Método que inicia a verificação se uma string é um palíndromo chamando o
  // método recursivo
  private static Boolean ehPalindromo(String texto) {
    return palindromo(texto, 0); // Inicia a verificação a partir do índice 0
  }

  private static Boolean isFim(String texto) {
    return (texto.length() == 3 && texto.charAt(0) == 'F' && texto.charAt(1) == 'I' && texto.charAt(2) == 'M');
  }

  private static void Resultado() {
    try (Scanner sc = new Scanner(System.in)) {

      String texto = sc.nextLine();

      while (!isFim(texto)) {
        // Verifica se a string atual é um palíndromo
        if (ehPalindromo(texto)) {
          System.out.println("SIM"); // Imprime "SIM" se for um palíndromo
        } else {
          System.out.println("NAO"); // Imprime "NAO" se não for um palíndromo
        }

        texto = sc.nextLine();
      }

      sc.close();
    }
  }

  public static void main(String[] args) {
    Resultado();
  }
}
