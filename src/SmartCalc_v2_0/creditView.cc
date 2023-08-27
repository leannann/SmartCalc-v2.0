#include "creditView.h"

#include "creditModel.h"
#include "ui_credit.h"

/**
 * @brief Конструктор класса Credit.
 * @param parent Указатель на родительский виджет (по умолчанию nullptr).
 *
 * Конструктор инициализирует объект класса Credit и создает пользовательский
 * интерфейс с помощью функции setupUi(), которая настроена на работу с данным
 * объектом.
 */
s21::Credit::Credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

/**
 * @brief Деструктор класса Credit.
 *
 * Деструктор освобождает память, выделенную для объекта пользовательского
 * интерфейса ui, вызывая оператор delete.
 */
s21::Credit::~Credit() { delete ui; }

/**
 * @brief Обработчик события нажатия на кнопку "Рассчитать".
 *
 * Эта функция вызывается при нажатии на кнопку "Рассчитать" на интерфейсе
 * кредитного калькулятора. Она считывает значения полей ввода, выполняет
 * соответствующие расчеты в зависимости от выбранного типа кредита (аннуитетный
 * или дифференцированный) и выводит результаты на интерфейс.
 */

void s21::Credit::on_pushButton_calculate_clicked() {
  // Получение значений с полей ввода
  QString str_amount = ui->input_amount->text();
  double amount = str_amount.toDouble();
  amount = fabs(amount);

  QString str_rate = ui->input_rate->text();
  double rate = str_rate.toDouble();
  rate = fabs(rate);

  QString str_term = ui->input_term->text();
  double term = str_term.toDouble();
  term = fabs(term);

  // Создание объекта структуры LoanInfo для хранения информации о кредите
  CreditModel::LoanInfo loanInfo;

  // Проверка выбранного типа кредита и выполнение соответствующих расчетов
  if (ui->annuity->isChecked()) {
    memset(&loanInfo, 0, sizeof(CreditModel::LoanInfo));
    loanInfo.amount = amount;
    loanInfo.rate = rate;
    loanInfo.term = static_cast<int>(term);
    loanInfo.type = CreditModel::LoanType::ANNUITY;

    // Вызов функции для расчета и получение результатов
    CreditModel::LoanResult loanResult = CreditModel::checkLoanType(loanInfo);

    // Преобразование результатов в строки и вывод на интерфейс
    QString p_resMonthlyPayment =
        QString::number(loanResult.monthly_payments[0], 'g', 6);
    QString p_overpayment = QString::number(loanResult.overpayment, 'g', 6);
    QString p_totalAmount = QString::number(loanResult.total, 'g', 6);

    ui->input_monthly->setText(p_resMonthlyPayment);
    ui->input_interest->setText(p_overpayment);
    ui->input_duty->setText(p_totalAmount);
  } else {
    // Аналогичный процесс для дифференцированного типа кредита
    memset(&loanInfo, 0, sizeof(CreditModel::LoanInfo));
    loanInfo.amount = amount;
    loanInfo.rate = rate;
    loanInfo.term = static_cast<int>(term);
    loanInfo.type = CreditModel::LoanType::DIFFERENTIATED;

    // Вызов функции для расчета и получение результатов
    CreditModel::LoanResult loanResult = CreditModel::checkLoanType(loanInfo);

    // Преобразование результатов в строки и вывод на интерфейс
    QString p_resMonthlyPayment =
        QString::number(loanResult.monthly_payments[0], 'g', 6);
    QString p_resMonthlyPaymentEND =
        QString::number(loanResult.monthly_payments[loanInfo.term - 1], 'g', 6);
    QString p_overpayment = QString::number(loanResult.overpayment, 'g', 6);
    QString p_totalAmount = QString::number(loanResult.total, 'g', 6);

    ui->input_monthly->setText(p_resMonthlyPayment + '-' +
                               p_resMonthlyPaymentEND);
    ui->input_interest->setText(p_overpayment);
    ui->input_duty->setText(p_totalAmount);
  }
}
