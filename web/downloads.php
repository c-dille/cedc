<?php return [
	"title" => "Téléchargements",
	"render" => function() { ?>
   <!-- Packages Section -->
    <div class="container mx-auto flex flex-wrap py-6" style="margin-top: 100px;">

        <!-- Page Title -->
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			Installation
        </h1>

        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Linux
		</h2>

		<pre class="text-center w-full">$ curl https://cédille.fr/[clé_licence]/install.sh | sh</pre>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			macOS
		</h2>

		<pre class="text-center w-full">$ curl https://cédille.fr/[clé_licence]/install.sh | sh</pre>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Windows
		</h2>

		<pre class="text-center w-full">$ Invoke-WebRequest -Uri "https://cédille.fr/[clé_licence]/install.ps1" -OutFile "install.ps1"; .\install.ps1</pre>
	</div>
	<hr class="mt-8"/>
	<div class="w-full text-center">
		<a class="mt-8 mx-auto inline-block bg-gray-500 text-white text-sm px-5 py-2 rounded-full text-lg" href="#">Plugin VSCode</a>
	</div>
	<br/>
	<br/>

	<?php
	}
];
