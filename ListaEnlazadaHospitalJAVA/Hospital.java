/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

import java.util.Scanner;

/**
 *
 * @author emiro
 */
public class Hospital {

    public static void main(String[] args) {
        Scanner lector = new Scanner(System.in);
        ListaPacientes listaPacientes = new ListaPacientes();

        listaPacientes.agregarPaciente(new Paciente("Juan Perez", 2));
        listaPacientes.agregarPaciente(new Paciente("Ana Gomez", 1));
        listaPacientes.agregarPaciente(new Paciente("Luis Torres", 3));
        listaPacientes.agregarPaciente(new Paciente("Maria Lopez", 1));

        /*
        System.out.println("Lista de pacientes ordenada por prioridad:");
        listaPacientes.mostrarPacientes();

        System.out.println("\nAtendiendo al siguiente paciente:");
        listaPacientes.atenderPaciente();

        System.out.println("\nLista de pacientes después de atender uno:");
        listaPacientes.mostrarPacientes();

        */
        int opcion;
        do{
        System.out.println("¿Qué desea hacer? mostrar pacientes(1) / atender paciente(2) / Salir(0)");
        opcion = lector.nextInt();
        if(opcion == 1){
            listaPacientes.mostrarPacientes();
        }
        if(opcion == 2){
            listaPacientes.atenderPaciente();
        }
        }while(opcion != 0);
        
        
    }
}
