/*!
\file
\brief Заголовочный файл с объявлениям класса DepositCalculator для вычисление
суммы вклада с учетом различных параметров
*/

#ifndef CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_DEPOSITMODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_DEPOSITMODEL_H_

#include <cmath>

/**
 * @brief Класс для расчета параметров депозита.
 *
 * Данный класс предоставляет методы для вычисления депозита с учетом различных
 * параметров.
 */
namespace s21 {
class DepositCalculator {
 public:
  /**
   * @brief Рассчитывает параметры депозита.
   *
   * Метод вычисляет параметры депозита, такие как начисленные проценты,
   * итоговая сумма депозита и налоговая сумма.
   *
   * @param deposit_amount Сумма депозита.
   * @param period Период в месяцах.
   * @param rate Годовая процентная ставка.
   * @param tax_rate Процентная ставка налога.
   * @param accrued Начисленные проценты.
   * @param deposit_end Итоговая сумма депозита по окончанию срока.
   * @param tax_amount Налоговая сумма.
   * @param capital_flag Флаг капитализации процентов (1 - с капитализацией, 0 -
   * без капитализации).
   * @param replenishment Сумма пополнения депозита каждый период.
   * @param withdrawals Сумма снятия с депозита каждый период.
   * @param periodicity Периодичность начисления процентов (1 - ежемесячно, 3 -
   * квартально и т.д.).
   *
   * @note Метод работает с различными сценариями депозита, включая разные
   * режимы начисления процентов и операций пополнения/снятия.
   *
   * @return void
   */
  void deposit(double deposit_amount, double period, double rate,
               double tax_rate, double& accrued, double& deposit_end,
               double& tax_amount, int capital_flag, double replenishment,
               double withdrawals, double periodicity) noexcept;

  /**
   * @brief Проверяет периодичность начисления процентов.
   *
   * Метод проверяет периодичность начисления процентов и вычисляет количество
   * периодов начисления.
   *
   * @param period Период вклада в месяцах.
   * @param periodicity Периодичность начисления процентов (1 - ежемесячно, 3 -
   * квартально и т.д.).
   * @param count Количество периодов начисления процентов.
   *
   * @note Метод используется для корректного расчета сценариев депозита с
   * разной периодичностью начисления процентов.
   *
   * @return void
   */
  void check_periodicity(double period, double periodicity,
                         int& count) noexcept;

  /**
   * @brief Рассчитывает депозит с учетом капитализации процентов.
   *
   * Метод рассчитывает параметры депозита с учетом капитализации процентов и
   * различных операций.
   *
   * @param period Период вклада в месяцах.
   * @param deposit_end Итоговая сумма депозита по окончанию срока.
   * @param accrued Начисленные проценты.
   * @param replenishment Сумма пополнения депозита каждый период.
   * @param withdrawals Сумма снятия с депозита каждый период.
   * @param rate Годовая процентная ставка.
   * @param tmp Временное значение для расчета процентов.
   * @param tmp_1 Временное значение для расчета итоговой суммы.
   * @param count Количество периодов начисления процентов.
   *
   * @note Метод рассчитывает депозит с учетом капитализации процентов и
   * различных операций внесения и снятия средств.
   *
   * @return void
   */
  void capital(double period, double& deposit_end, double& accrueds,
               double replenishment, double withdrawals, double rate,
               double& tmp, double& tmp_1, int& count) noexcept;

  /**
   * @brief Рассчитывает депозит без капитализации процентов и с дополнительными
   * операциями.
   *
   * Метод рассчитывает параметры депозита без капитализации процентов и с
   * дополнительными операциями.
   *
   * @param period Период вклада в месяцах.
   * @param deposit_end Итоговая сумма депозита по окончанию срока.
   * @param accrued Начисленные проценты.
   * @param replenishment Сумма пополнения депозита каждый период.
   * @param withdrawals Сумма снятия с депозита каждый период.
   * @param rate Годовая процентная ставка.
   * @param tmp Временное значение для расчета процентов.
   * @param tmp_1 Временное значение для расчета итоговой суммы.
   * @param count Количество периодов начисления процентов.
   *
   * @note Метод рассчитывает депозит без капитализации процентов и с
   * дополнительными операциями внесения и снятия средств.
   *
   * @return void
   */
  void without_capital(double period, double& deposit_end, double& accrueds,
                       double replenishment, double withdrawals, double rate,
                       double& tmp, double& tmp_1, int& count) noexcept;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SMARTCALC_V2_0_DEPOSITMODEL_H_
