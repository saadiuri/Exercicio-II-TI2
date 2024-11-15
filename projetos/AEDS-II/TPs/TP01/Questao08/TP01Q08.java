// package Questao08;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class TP01Q08 {

    private static void arquivo() {
        try (Scanner scanner = new Scanner(System.in)) {

            // Passo 1: Ler o número de valores reais (n)
            if (scanner.hasNextInt()) {
                int n = scanner.nextInt();

                // Nome do arquivo onde os valores serão armazenados
                String nomeArquivo = "valores.txt";

                try (RandomAccessFile arquivo = new RandomAccessFile(nomeArquivo, "rw")) {
                    // Passo 2: Criar um arquivo de acesso aleatório para escrita

                    // Escrever os valores reais no arquivo
                    for (int i = 0; i < n; i++) {
                        if (scanner.hasNextDouble()) {
                            double valor = scanner.nextDouble();
                            arquivo.writeDouble(valor);
                        }
                    }
                } catch (IOException e) {
                    System.err.println("Erro ao manipular o arquivo para escrita: " + e.getMessage());
                }

                // Reabrir o arquivo para leitura
                try (RandomAccessFile arquivo = new RandomAccessFile(nomeArquivo, "r")) {
                    // Passo 4: Ler os valores de trás para frente
                    for (int i = n - 1; i >= 0; i--) {
                        arquivo.seek(i * 8); // Mover o ponteiro para a posição do valor i (cada double ocupa 8 bytes)
                        double valor = arquivo.readDouble(); // Ler o valor
                        System.out.println(valor); // Imprimir o valor na tela
                    }
                } catch (IOException e) {
                    System.err.println("Erro ao manipular o arquivo para leitura: " + e.getMessage());
                }

            } else {
                System.err.println("Erro: Número inteiro esperado, mas não encontrado.");
            }
        }
    }

    public static void main(String[] args) {
        arquivo();
    }
}
