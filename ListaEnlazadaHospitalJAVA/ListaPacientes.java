/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

import java.util.LinkedList;

/**
 *
 * @author emiro
 */
public class ListaPacientes {
    private LinkedList<Paciente> lista;

    public ListaPacientes() {
        this.lista = new LinkedList<>();
    }

    public void agregarPaciente(Paciente nuevoPaciente) {
        if (lista.isEmpty()) {
            lista.add(nuevoPaciente);
            return;
        }

        int i = 0;
        for (; i < lista.size(); i++) {
            if (nuevoPaciente.getPrioridad() < lista.get(i).getPrioridad()) {
                break;
            }
        }
        lista.add(i, nuevoPaciente);
    }

    public void mostrarPacientes() {
        for (Paciente p : lista) {
            System.out.println(p);
        }
    }

    public void atenderPaciente() {
        if (!lista.isEmpty()) {
            Paciente atendido = lista.removeFirst();
            System.out.println("Atendiendo a: " + atendido);
        } else {
            System.out.println("No hay pacientes para atender.");
        }
    }
}
