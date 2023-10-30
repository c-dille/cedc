<?php return [
	"title" => "Tarifs",
	"render" => function() { ?>
    <div class="relative container mx-auto py-6" style="margin-top: 100px; ">
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			Tarifs
        </h1>
		<br/>
		<br/>
		<table class="mx-auto" style="height: fit-content;">
			<tr><th></th><th>Basique</th><th>Profesionnels</th><th>Entreprise</th></tr>
			<tr><td>Accès aux executables</td><td>✓</td><td>✓</td><td>✓</td></tr>
			<tr><td>Usage commercial pour serveurs</td><td></td><td>✓</td><td>✓</td></tr>
			<tr><td>Usage commercial pour clients</td><td></td><td></td><td>✓</td></tr>
			<tr><td>Support prioritaire</td><td></td><td></td><td> ✓ </td></tr>
			<tr><td>Support de Clang / GCC pour des performances optimales</td><td></td><td></td><td> ✓ </td></tr>

			<tr><th>Prix</th><th>15€*</th><th>50€</th><th>500€</th></tr>
		</table>
	</div>
	<div class="w-full text-center mt-0">
		<p>
			* Gratuit pour les étudiants.<br/>
		</p>
	</div>
	<hr class="mt-8"/>
	<div class="w-full text-center">
		<a class="mt-8 mx-auto inline-block bg-gray-500 text-white text-sm px-5 py-2 rounded-full text-lg" href="#">Acheter</a>
		<br/>
		<br/>
		<p>Pour des adaptations personnalisées correspondant à vos projets et workflows, <a href="/contact">n'hésitez pas à nous contacter</a>.</p>

	</div>
<?php }
];
