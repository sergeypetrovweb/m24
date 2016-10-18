<?php
$brands = array();
foreach ($settings['items'] as $key => $val) {
    if (is_int($key)) {
        $brands[] = $settings['items'][$key];
    }
}
$brands_col = array_chunk($brands, 5);
?>

<div id="brands">
    <div class="container">
        <div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
            <!-- Wrapper for slides -->
            <div class="carousel-inner" role="listbox">
                <?php foreach ($brands_col as $id => $column): ?>
                    <div class="item <?php $id == 0 ? print 'active' : null ?>">
                        <?php foreach ($column as $col_id => $brand):?>
                            <?php
                            $img = file_load($brand['img']);
                            $img = theme(
                                'image_style',
                                array(
                                    'path' => $img->uri,
                                    'style_name' => 'flight_modern__brands',
                                )
                            );
                            ?>

                            <a href="<?php print $brand['url'] ?>"><?php print $img ?></a>

                        <?php endforeach; ?>

                    </div>
                <?php endforeach; ?>
            </div>

            <!-- Controls -->
            <a class="left carousel-control" href="#carousel-example-generic" role="button" data-slide="prev">
                <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
                <span class="sr-only">Previous</span>
            </a>
            <a class="right carousel-control" href="#carousel-example-generic" role="button" data-slide="next">
                <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
                <span class="sr-only">Next</span>
            </a>
        </div>
    </div>
</div>