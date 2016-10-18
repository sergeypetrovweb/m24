<?php $path = drupal_get_path('theme', 'flight_modern') ?>
<div id="content">
  <div class="container">

    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block">
      <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 thumb_hotel_buy"><img src="/<?php print $path; ?>/images/buy_hotel_img1.png"></div>
      <div class="col-lg-8 col-md-8 col-sm-12 col-xs-12 content_hotel_buy">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 block_name">
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12">
            <span class="buy_name">Old City Inn</span>
            <img src="/<?php print $path; ?>/images/big_star_active.png">
            <img src="/<?php print $path; ?>/images/big_star_active.png">
            <img src="/<?php print $path; ?>/images/big_star_active.png">
            <img src="/<?php print $path; ?>/images/big_star_active.png">
            <img src="/<?php print $path; ?>/images/big_star.png">
          </div>
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 value_users">
            Оценка посетителей <span class="value">8,9</span>
          </div>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
          <img src="/<?php print $path; ?>/images/map_orange.png"> Binbirdirek Mah. Terzihane Sok. No:17 SultanahmetУслуги
          <a href="#">Показать на карте</a>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12">
            <a href="">Стандартный двухместный номер<br>(двуспальная или 2 односпальные кровати)</a>
          </div>
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 text-right"><a href="#" class="other_rooms">другие номера</a></div>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 time">
          Время пребывания: <span>24.07- 31.07 (7 ночей)</span>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 numbers">
          Номера должны быть выплачены до 2 сентября 0:00 GMT(+0500)
        </div>
      </div>
      <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 you_data">
        <h1>Ваши данные</h1>
        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-4"><label for="name">Имя</label><input type="text" id="name"></div>
        <div class="col-lg-3 col-md-3 col-sm-3 col-xs-4"><label for="name">Фамилия</label><input type="text" id="name"></div>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-4">
          <label for="country">Страна</label>
          <select name="" id="country">
            <option> </option>
            <option> </option>
            <option> </option>
          </select>
        </div>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-4"><label for="email">E-mail</label><input type="text" id="email"></div>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-4"><label for="phone">Телефон</label><input type="tel" id="phone"></div>
      </div>

      <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 payment">
        <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12">
          <h3>Оплата</h3>
          <table class="desktop">
            <tr>
              <td>Цена за 1 ночь, <img src="/<?php print $path; ?>/images/clock_blue.png"></td>
              <td>Время пребывания, ночей</td>
              <td>Кол-во чел</td>
              <td>Всего, <img src="/<?php print $path; ?>/images/clock_blue.png"></td>
            </tr>
            <tr>
              <td>15</td>
              <td>7</td>
              <td>2</td>
              <td>167</td>
            </tr>
          </table>
          <table class="mobile">
            <tr>
              <td>Цена за 1 ночь, <img src="/<?php print $path; ?>/images/clock_blue.png"></td>
              <td>15</td>
            </tr>
            <tr>
              <td>Время пребывания, ночей</td>
              <td>7</td>
            </tr>
            <tr>
              <td>Кол-во чел</td>
              <td>2</td>
            </tr>
            <tr>
              <td>Всего, <img src="/<?php print $path; ?>/images/clock_blue.png"></td>
              <td>167</td>
            </tr>
          </table>
          <h3>Информация о номере</h3>
          <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 mb-20">
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-6">
              <ul class="style">
                <li>Бесплатная отмена</li>
                <li>Завтрак включен</li>
                <li>Оплата в отеле</li>
              </ul>
            </div>
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-6">
              <ul class="style">
                <li>Бесплатная отмена</li>
                <li>Завтрак включен</li>
                <li>Оплата в отеле</li>
              </ul>
            </div>
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-4 hidden-xs">
              <ul class="style">
                <li>Бесплатная отмена</li>
                <li>Завтрак включен</li>
                <li>Оплата в отеле</li>
              </ul>
            </div>
          </div>
          <h3>Сроки, условия и ограничения</h3>
          <ul class="style">
            <li>В случае отмены бронирования до 2 сентября, комисиия не взимается</li>
            <li>В период с 3 сентября до 5 сентября, комиссия за отмену брони составит 155 M</li>
            <li>Не допускается нахождение животных в ном</li>
          </ul>
        </div>
      </div>
      <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 text-center accept">
        <input type="checkbox" id="insurance1" class="insurance_input"><label for="insurance1"><span></span>Я принимаю условия и ограничения </label>
        <input type="button" value="Забронировать" class="default-bb">
      </div>
    </div>

  </div>
</div>