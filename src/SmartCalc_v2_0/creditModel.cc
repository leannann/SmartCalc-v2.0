#include "creditModel.h"

/**
 * @brief Функция для определения типа кредита и выполнения расчетов в
 * зависимости от выбранного типа.
 *
 * Эта функция принимает информацию о кредите в виде структуры `LoanInfo`,
 * включающей тип кредита (`LoanType`) и другие параметры кредита. В зависимости
 * от выбранного типа кредита (аннуитетный или дифференцированный), функция
 * вызывает соответствующую функцию для расчетов (`annuity` или
 * `differentiated`) и возвращает результат расчетов в виде структуры
 * `LoanResult`.
 *
 * @param loan Информация о кредите, включая тип кредита и параметры.
 * @return Результат расчетов кредита, включая ежемесячный платеж, переплату по
 * кредиту и общую сумму выплат.
 */
s21::CreditModel::LoanResult s21::CreditModel::checkLoanType(
    LoanInfo loan) noexcept {
  // Проверяем тип кредита: аннуитетный или дифференцированный
  // В зависимости от типа вызываем соответствующую функцию для расчетов
  return loan.type == LoanType::ANNUITY ? annuity(loan) : differentiated(loan);
}

/**
 * @brief Функция для расчета кредита по аннуитетной схеме.
 *
 * Эта функция принимает информацию о кредите в виде структуры `LoanInfo`,
 * содержащей параметры кредита. Внутри функции производятся вычисления для
 * аннуитетного платежа, включая ежемесячный платеж, переплату по кредиту и
 * общую сумму выплат. Результат расчетов возвращается в виде структуры
 * `LoanResult`.
 *
 * @param loan Информация о кредите, включая параметры.
 * @return Результат расчета кредита по аннуитетной схеме, включая ежемесячный
 * платеж, переплату по кредиту и общую сумму выплат.
 */
s21::CreditModel::LoanResult s21::CreditModel::annuity(LoanInfo loan) noexcept {
  LoanResult outLoan;

  // Инициализация параметров кредита и проверка наличия ошибок
  std::string error = initLoan(loan);

  if (!error.empty())
    outLoan.message = error;

  else {
    // Вычисление параметров для аннуитетного платежа
    double _amount = loan.amount;
    double _rate = loan.rate;
    double _rate_per_month = _rate / 1200;
    double _term = loan.term;
    double _rate_months = std::pow((1 + _rate_per_month), _term);
    double _coefficient = (_rate_per_month * _rate_months) / (_rate_months - 1);
    double _payment = _coefficient * _amount;

    // Вычисление общей суммы выплат, переплаты по кредиту и формирование
    // массива ежемесячных платежей
    outLoan.total = _payment * _term;
    outLoan.overpayment = outLoan.total - _amount;
    outLoan.monthly_payments.resize(static_cast<size_t>(_term), _payment);
  }

  return outLoan;
}

/**
 * @brief Функция для расчета кредита по дифференцированной схеме.
 *
 * Эта функция принимает информацию о кредите в виде структуры `LoanInfo`,
 * содержащей параметры кредита. Внутри функции производятся вычисления для
 * дифференцированного платежа, включая ежемесячные платежи, переплату по
 * кредиту и общую сумму выплат. Результат расчетов возвращается в виде
 * структуры `LoanResult`.
 *
 * @param loan Информация о кредите, включая параметры.
 * @return Результат расчета кредита по дифференцированной схеме, включая
 * ежемесячные платежи, переплату по кредиту и общую сумму выплат.
 */
s21::CreditModel::LoanResult s21::CreditModel::differentiated(
    LoanInfo loan) noexcept {
  LoanResult out_l;

  double _amount = loan.amount;
  double _rate = loan.rate;
  double _rate_per_month = _rate / 1200;
  double _term = loan.term;
  double _balance = _amount;
  double _amount_per_month = _amount / _term;

  // Инициализация массива для ежемесячных платежей
  out_l.monthly_payments.resize(static_cast<size_t>(_term));

  // Вычисление ежемесячных платежей, переплаты по кредиту и общей суммы выплат
  for (int i = 0; i < _term; ++i) {
    out_l.monthly_payments[i] = _amount / _term + _balance * _rate_per_month;
    _balance -= _amount_per_month;
    out_l.total += out_l.monthly_payments[i];
  }
  out_l.overpayment = out_l.total - _amount;

  return out_l;
}

/**
 * @brief Инициализация параметров кредита и проверка их корректности.
 *
 * Эта функция принимает информацию о кредите в виде структуры `LoanInfo` и
 * производит инициализацию и проверку параметров. В случае, если какой-либо
 * параметр кредита некорректен (меньше или равен нулю), функция возвращает
 * строку с описанием ошибки. В противном случае, функция возвращает пустую
 * строку, что означает успешную инициализацию и отсутствие ошибок.
 *
 * @param loan Информация о кредите, включая параметры.
 * @return Строка с описанием ошибки, если параметры кредита некорректны, или
 * пустая строка, если параметры корректны.
 */
std::string s21::CreditModel::initLoan(LoanInfo loan) noexcept {
  if (!(loan.amount && loan.rate && loan.term))
    return "ERROR: Invalid credit parameters!";

  if (loan.amount <= 0 || loan.term <= 0 || loan.rate <= 0) {
    if (loan.amount <= 0) return "[1] Некорректная сумма кредита!";
    if (loan.rate <= 0) return "[2] Некорректная процентная ставка!";
    if (loan.term <= 0) return "[3] Некорректный срок кредита!";
  }
  return "";
}
