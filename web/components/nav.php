<?php
	const style_default_menu_item = " text-gray-400 hover:text-gray-200";
	const style_active_menu_item = "text-white";

	function render_menu_item($url, $k)
	{
		?>
			<li class="mr-3">
                <a class="inline-block py-2 px-4 no-underline <?=$_SERVER["REQUEST_URI"] == $url ? style_active_menu_item : style_default_menu_item  ?>"
					href="<?=$url?>"
				>
						<?=$k?>
				</a>
            </li>
		<?php
	}
?>
<nav class="bg-gray-900 p-4 mt-0 fixed w-full z-10 top-0">
        <div class="container mx-auto flex flex-wrap items-center">
            <div class="flex w-full md:w-1/2 justify-center md:justify-start text-white font-extrabold">
                <a class="text-white no-underline hover:text-gray-200 text-2xl pl-2" href="/">
					<img src="/assets/cedilla-white.svg" alt="Cédille Hero Image" width="40" height="auto"/>
				</a>
            </div>
            <div class="flex w-full pt-2 content-center justify-between md:w-1/2 md:justify-end">
                <ul class="list-reset flex justify-between flex-1 md:flex-none items-center">
					<?=render_menu_item("/", "Accueil")?>
					<?=render_menu_item("/téléchargements", "Téléchargements")?>
					<?=render_menu_item("/documentation", "Documentation")?>
					<?=render_menu_item("/paquets", "Paquets")?>
					<?=render_menu_item("/tarifs", "Tarifs")?>
					<?=render_menu_item("/contact", "Contactez-nous")?>
                </ul>
            </div>
        </div>
    </nav>
