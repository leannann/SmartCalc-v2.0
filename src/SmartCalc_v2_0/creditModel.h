/*!
\file
\brief Заголовочный файл с объявлением класса creditModel реализующего
модель кредитного калькялятора.
*/

#ifndef CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITMODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITMODEL_H_

#include <cmath>
#include <string>
#include <vector>

/**
 * @namespace s21
 * @brief Пространство имен для модуля кредитного калькулятора.
 */
namespace s21 {
/**
 * @class CreditModel
 * @brief Класс, реализующий модель кредитного калькулятора.
 *
 * Этот класс содержит методы для расчета кредитных выплат в различных режимах.
 * Он определяет структуры `LoanInfo` и `LoanResult` для хранения информации о
 * кредите и результатов расчетов.
 */
class CreditModel {
 public:
  /**
   * @enum LoanType
   * @brief Типы кредитов: аннуитетный и дифференцированный.
   */
  enum LoanType { ANNUITY, DIFFERENTIATED };

  /**
   * @struct LoanInfo
   * @brief Структура для хранения информации о кредите.
   */
  struct LoanInfo {
    double amount; /**< Сумма кредита. */
    double rate;   /**< Процентная ставка. */
    int term;      /**< Срок кредита в месяцах. */
    LoanType type; /**< Тип кредита (аннуитетный или дифференцированный). */
  };

  /**
   * @struct LoanResult
   * @brief Структура для хранения результатов расчетов кредита.
   */
  struct LoanResult {
    int err;             /**< Код ошибки (0 - нет ошибки). */
    std::string message; /**< Сообщение об ошибке (если есть). */
    std::vector<double> monthly_payments; /**< Массив ежемесячных платежей. */
    double overpayment; /**< Переплата по кредиту (проценты). */
    double total; /**< Общая сумма выплаты по кредиту. */
  };

  /**
   * @brief Проверка типа кредита и выполнение соответствующих расчетов.
   * @param loan Информация о кредите.
   * @return Результат расчетов для заданного типа кредита.
   */
  static LoanResult checkLoanType(LoanInfo loan) noexcept;

  /**
   * @brief Расчет кредита в режиме аннуитетного платежа.
   * @param loan Информация о кредите.
   * @return Результат расчетов для аннуитетного кредита.
   */
  static LoanResult annuity(LoanInfo loan) noexcept;

  /**
   * @brief Расчет кредита в режиме дифференцированного платежа.
   * @param loan Информация о кредите.
   * @return Результат расчетов для дифференцированного кредита.
   */
  static LoanResult differentiated(LoanInfo loan) noexcept;

  /**
   * @brief Инициализация параметров кредита и проверка их корректности.
   * @param loan Информация о кредите.
   * @return Строка с описанием ошибки (если параметры некорректны), иначе
   * пустая строка.
   */
  static std::string initLoan(LoanInfo loan) noexcept;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_CREDITMODEL_H_
