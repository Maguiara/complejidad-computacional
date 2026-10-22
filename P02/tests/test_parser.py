"""Pruebas de validación del Parser real mediante la interfaz de consola.

Ejecutar desde P02: python3 tests/test_parser.py
Requiere g++ con soporte C++20. Compila y crea los casos en una carpeta temporal.
"""

from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
BASE = ["q0 qf", "a b", "a b .", "q0", ".", "qf", "1",
        "q0 a qf a R"]
MULTITAPE = ["q0 qf", "a b", "a b .", "q0", ".", "qf", "2",
             "q0 a . qf b a R S"]


class ParserTest(unittest.TestCase):
    """Comprueba los campos y todas las posiciones de las transiciones."""

    @classmethod
    def setUpClass(cls):
        cls.directory = tempfile.TemporaryDirectory(prefix="p02_parser_")
        cls.addClassCleanup(cls.directory.cleanup)
        cls.work = Path(cls.directory.name)
        cls.executable = cls.work / "p02"
        subprocess.run(
            ["g++", "-std=c++20", "-Wall", "-Wextra", "-Wpedantic",
             "-I" + str(ROOT / "include"),
             *map(str, sorted((ROOT / "src").glob("*.cc"))),
             "-o", str(cls.executable)], check=True)

    def execute(self, lines):
        """Invoca el programa con una configuración temporal y sin entradas."""
        config = self.work / "machine.txt"
        config.write_text("\n".join(lines) + ("\n" if lines else ""),
                          encoding="utf-8")
        return subprocess.run(
            [str(self.executable), "-config", str(config)],
            input="", text=True, capture_output=True, timeout=5)

    def assert_invalid(self, lines, line, message):
        """Verifica rechazo, diagnóstico y número de línea física."""
        result = self.execute(lines)
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn(f"machine.txt: linea {line}:", result.stderr)
        self.assertIn(message, result.stderr)

    def test_valid_definitions(self):
        for lines in [BASE, MULTITAPE, BASE[:7],
                      ["# comentario", "", *BASE, "# comentario final"],
                      [line + " # comentario" for line in BASE]]:
            with self.subTest(lines=lines):
                result = self.execute(lines)
                self.assertEqual(result.returncode, 0, result.stderr)

    def test_header_fields(self):
        cases = [
            (1, "aa b", "un caracter"),
            (2, "a bb .", "un caracter"),
            (2, "a .", "Simbolo de entrada"),
            (3, "missing", "Estado inicial"),
            (3, "q0 qf", "Formato del estado inicial"),
            (4, "z", "blanco"),
            (4, "a", "blanco"),
            (4, "..", "Simbolo blanco"),
            (4, ". extra", "Simbolo blanco"),
            (5, "qf missing", "Estado final"),
            (6, "0", "Numero de cintas"),
            (6, "-1", "Numero de cintas"),
            (6, "+1", "Numero de cintas"),
            (6, "1x", "Numero de cintas"),
            (6, "1 2", "Numero de cintas"),
            (6, "18446744073709551616", "Numero de cintas"),
        ]
        for index, value, message in cases:
            with self.subTest(index=index, value=value):
                lines = BASE.copy()
                lines[index] = value
                self.assert_invalid(lines, index + 1, message)

    def test_missing_header_lines(self):
        for length in range(7):
            with self.subTest(length=length):
                self.assert_invalid(BASE[:length], length, "Falta")

    def test_all_transition_fields_on_each_tape(self):
        cases = [(0, "missing", "Estado de transicion"),
                 (3, "missing", "Estado de transicion")]
        for index in [1, 2, 4, 5]:
            cases.extend([(index, "z", "fuera del alfabeto"),
                          (index, "aa", "un caracter")])
        for index in [6, 7]:
            cases.extend([(index, "X", "Movimiento no valido"),
                          (index, "RR", "un caracter")])
        for index, value, message in cases:
            with self.subTest(index=index, value=value):
                lines = MULTITAPE.copy()
                tokens = lines[-1].split()
                tokens[index] = value
                lines[-1] = " ".join(tokens)
                self.assert_invalid(lines, 8, message)

    def test_transition_field_count(self):
        for transition in ["q0 a qf a", "q0 a qf a R extra",
                           "texto sobrante", "q0 a . qf a . R S"]:
            with self.subTest(transition=transition):
                self.assert_invalid([*BASE[:7], transition], 8,
                                    "Numero de campos")

    def test_duplicate_conditions(self):
        for transition in [BASE[-1], "q0 a q0 b L"]:
            with self.subTest(transition=transition):
                self.assert_invalid([*BASE, transition], 9, "no determinista")

    def test_last_line_and_physical_line_numbers(self):
        self.assert_invalid([*BASE, "", "# comentario", "qf b qf z S"],
                            11, "Simbolo de escritura")
        self.assert_invalid([*BASE, "qf b missing b S"], 9,
                            "Estado de transicion")

    def test_exercise_definitions(self):
        for name in ["mt_ejercicio1.txt", "mt_ejercicio2.txt"]:
            with self.subTest(name=name):
                lines = (ROOT / "docs" / name).read_text(
                    encoding="utf-8").splitlines()
                result = self.execute(lines)
                self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
