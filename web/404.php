<?php return [
	"title" => "Not found",
	"render" => function() { global $uri; ?>
   <!-- Packages Section -->
    <div class="container mx-auto flex flex-wrap py-6" style="margin-top: 100px;">

        <!-- Page Title -->
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
           404
        </h1>

        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Page non trouvé : <br/><?=$uri?>
		</h2>

	</div>
		<?php
	}
];
