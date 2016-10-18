
<?php $path = drupal_get_path('theme', 'flight_modern'); ?>

<div id="breadcrumbs">
    <div class="container">
        <img src="images/breadcrumbs_home.png"> <a href="#">Бронирование авиабилетов</a>
    </div>
</div>


<div id="filter">
    <div class="container">

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 company_details">
            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 company_logo">
                <img src="/<?php print $path ?>/images/avia_company_logo.png">
                <a href="#">Baku - Istanbul</a>
                <span><i class="glyphicon glyphicon-plane"></i> J2 223</span>
            </div>
            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                <p><i class="glyphicon glyphicon-time"></i> Вылет в <span class="red_time">23:40</span><br>
                    18 апреля 2015 г.<br>
                    из а/п Домодедово (DME)</p>
            </div>
            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                <p>Время в пути 3ч 20 мин<br>
                    экономкласс</p>
            </div>
            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                <p>Прилёт в <span class="red_time">03:30</span><br>
                    26 апреля 2015 г.<br>
                    в а/п Гейдар Алиев (GYD)</p>
            </div>
        </div>

    </div>
</div>

<div id="content">
<div class="container">

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 filling_date">
    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 title_content">Заполните данные пассажиров</div>
    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 data">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 filling_data_input">
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
                <div class="indent">
                    <label for="date1">Имя/Фамилия </label>
                    <input type="text" id="name">
                </div>
            </div>
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
                <div class="indent">
                    <label for="date1">Дата рождения</label>
                    <input type="text" id="date1" placeholder="дд.мм.гггг">
                </div>
            </div>
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 citizenship">
                <div class="indent">
                    <label for="citizenship1">Гражданство</label>
                    <input type="text" id="county">
                </div>
            </div>
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
                <div class="indent">
                    <label for="n_pasport1">Дата рождения</label>
                    <input type="text" id="n_pasport1">
                </div>
            </div>
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
                <div class="indent">
                    <label for="validity1">Срок действия</label>
                    <input type="text" id="validity1" placeholder="дд.мм.гггг">
                </div>
            </div>
            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
                <div class="indent">
                    <label for="m_card1">Мильная карта</label>
                    <input type="text" id="m_card1">
                </div>
            </div>
        </div>
    </div>
</div>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 additional_services">
    <div class="title_line">
        <p class="title_services">дополнительные службы</p>
        <span class="line"></span>
    </div>
    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 insurance">
        <p>1.Страховка</p>
        <ul>
            <li><input type="checkbox" id="insurance1" class="insurance_input"><label for="insurance1">1.1 Страхование путешествий</label></li>
            <li><input type="checkbox" id="insurance2" class="insurance_input"><label for="insurance2">1.2 Страхование багажа</label></li>
            <li><input type="checkbox" id="insurance3" class="insurance_input"><label for="insurance3">1.3 Страхование жизни</label></li>
        </ul>
    </div>
    <div class="col-lg-9 col-md-9 col-sm-9 col-xs-12 info">
        <i class="glyphicon glyphicon-info-sign"></i>
        <p>Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,
            when an unknown printer took a galley of type and scrambled it to make a type
            specimen book. It has survived not only five centuries, but also the leap into electronic
            typesetting, remaining essentially unchanged. It was popularised in the 1960s with the
            release of Letraset sheets containing Lorem Ipsum passages, and more recently with
            desktop publishing software </p>
    </div>
</div>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 payment_data">
    Введите данные об оплате
    <div class="pay_info">
        <span>16 775</span><img src="/<?php print $path ?>/images/clock_gray.png"><br>
        Картой через авиакомп.<br>
        Azal
    </div>
</div>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 card_data">
    <div class="col-lg-4 col-md-4 col-sm-6 col-xs-12 card_number">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_card">
            <p>Номер карты</p>
            <input type="text" class="number">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 inline_el">
                <span>Срок<br>действия</span>
                <div><label>Месяц</label>
                    <input type="text" placeholder="05"></div>
                <div><label>год</label>
                    <input type="text" placeholder="17"></div>
                <img src="/<?php print $path ?>/images/card.png">
            </div>
        </div>
    </div>
    <div class="col-lg-4 col-md-4 col-sm-6 col-xs-12 card_cvv">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_card">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 card_line"></div>
            <div class="col-lg-11 col-md-11 col-sm-11 col-xs-11 card_cvv_info">
                <div class="col-lg-9 col-md-9 col-sm-9 col-xs-12">
                    <p>CVV или CVC — трехзначный код на обратной стороне карты</p>
                </div>
                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                    <label>CVV/CVC</label>
                    <input type="text">
                </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 payments_metod_card">
                <img src="/<?php print $path ?>/images/visa.png">
                <img src="/<?php print $path ?>/images/mastercard.png">
                <img src="/<?php print $path ?>/images/visa_electron.png">
                <img src="/<?php print $path ?>/images/maestro.png">
            </div>
        </div>
    </div>
    <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 buy_protect">
        <img src="/<?php print $path ?>/images/lock.png">
        <h3>Покупки на mambo24travel.ru <br>надёжны и безопасны</h3>
        <p>Данные вашей банковской карты обрабатываются платежным центром PayU и защищены 256-битным шифрованием, обеспеченным компанией Comodo. Сайт отвечает стандартам безопасности платёжных систем Visa и MasterCard (PCI complliance).</p>
    </div>
    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 info_block">
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12"><img src="/<?php print $path ?>/images/palm.png"></div>
        <div class="col-lg-8 col-md-8 col-sm-7 col-xs-12">
            <h3>Хотите еще скидку? Забронируйте отель на Mambo24travel.ru</h3>
            <p>Забронируйте отель на одном из крупнейших и проверенных сайтов в индустрии</p>
        </div>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12"><input type="button" value="Выбрать отель" class="choice_hostel"></div>
        <input type="button" value="x" id="close">
    </div>
    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
        <input type="button" class="buy" value="Купить">
    </div>
</div>

</div>
</div>