/*!
\file
\brief Заголовочный файл с объявлениям класса Controller для пользовательского
интерфейса кредитного калькяулятора.
*/

#ifndef CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITVIEW_H_
#define CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITVIEW_H_

#include <QMainWindow>
#include <cmath>
#include <string>
#include <vector>

/**
 * @namespace Ui
 * @brief Пространство имен Ui содержит объявление пользовательского интерфейса.
 */

/**
 * @namespace s21
 * @brief Пространство имен s21 содержит классы, связанные с программой
 * кредитного калькулятора.
 */

/**
 * @class Ui::Credit
 * @brief Класс для пользовательского интерфейса главного окна.
 *
 * Этот класс представляет главное окно кредитного калькулятора и содержит
 * элементы управления для ввода параметров кредита и отображения результатов
 * расчетов.
 */

namespace Ui {
class Credit;
}

namespace s21 {
class Credit : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса Credit.
   * @param parent Указатель на родительский виджет (по умолчанию nullptr).
   */
  explicit Credit(QWidget *parent = nullptr);
  /**
   * @brief Деструктор класса Credit.
   */
  ~Credit();

 private slots:
  /**
   * @brief Слот для обработки события нажатия на кнопку "Рассчитать".
   *
   * Этот слот вызывается при нажатии на кнопку "Рассчитать" на интерфейсе
   * кредитного калькулятора. Он считывает значения полей ввода, выполняет
   * соответствующие расчеты и выводит результаты на интерфейс.
   */
  void on_pushButton_calculate_clicked(); /**< Указатель на объект
                                             пользовательского интерфейса. */

 private:
  Ui::Credit *ui;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITVIEW_H_
