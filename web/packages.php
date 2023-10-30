<?php return [
	"title" => "Paquets",
	"render" => function() { ?>
	<!-- Packages Section -->
    <div class="container mx-auto flex flex-wrap py-6" style="margin-top: 100px; ">

        <!-- Page Title -->
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
            Paquets officiels
        </h1>

        <!-- Search Bar -->
        <div class="w-full mx-auto mt-6">
            <div class="bg-white shadow p-4 flex">
                <span class="w-auto flex justify-end items-center text-gray-500 p-2">
                    <i class="fas fa-search"></i> <!-- You can use Font Awesome for icons -->
                </span>
                <input class="w-full rounded p-2" type="text" placeholder="Recherche par mots-clés" />
                <button class="bg-red-400 hover:bg-red-300 rounded text-white p-2 pl-4 pr-4">
                    <p class="font-semibold text-xs">Rechercher</p>
                </button>
            </div>
        </div>

        <!-- Package List -->
        <div class="w-full p-4">
            <div class="flex flex-wrap -mx-4">
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
                        <div class="p-4">
                            <h2 class="text-2xl font-bold">CPP</h2>
                            <p class="text-gray-600">Implémentation du <i>C-Pre-Processor</i> pour la cédille</p>
                            <div class="flex justify-between items-center mt-4">
                                <a href="https://cédille.org/paquets/cpp" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
                                <p class="text-gray-800 font-bold">v0.1</p> <!-- Version -->
                            </div>
                        </div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
                    </div>
                </div>
                <!-- Single Package Card -->
                <div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
                        <div class="p-4">
                            <h2 class="text-2xl font-bold">ç</h2>
                            <p class="text-gray-600">Superset standard pour le language C</p>
                            <div class="flex justify-between items-center mt-4">
                                <a href="https://cédille.org/paquets/ç" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
                                <p class="text-gray-800 font-bold">v0.2</p> <!-- Version -->
                            </div>
                        </div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span style="background-color: orange;" class="inline-block text-white text-sm px-3 py-1 rounded-full">Beta</span> <!-- Étiquette d'état -->
    					</div>
                    </div>
                </div>
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">Ç</h2>
							<p class="text-gray-600">Superset standard pour le language C++</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/Ç" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.1</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">ODBC</h2>
							<p class="text-gray-600">Pilote de base de données SQL générique</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/ODBC" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.1</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">Libpq</h2>
							<p class="text-gray-600">Pilote de base de données spécifique à PostgreSQL</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/Libpq" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.1</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">Liburing</h2>
							<p class="text-gray-600">Interface de programmation asynchronne pour liburing en ç</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/Liburing"  class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.2</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>
				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">LibUV</h2>
							<p class="text-gray-600">Interface de programmation asynchronne pour libuv en ç</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/LibUV" class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v1.0</p> <!-- Version -->
							</div>
							<div class="absolute mt-4 mr-4 top-0 right-0">
        						<span style="background-color: green;" class="inline-block text-white text-sm px-3 py-1 rounded-full">Opérationnel</span> <!-- Étiquette d'état -->
    						</div>
						</div>
					</div>
				</div>

				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">DOM</h2>
							<p class="text-gray-600">DOM support</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/DOM"  class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.3</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-500 text-white text-sm px-3 py-1 rounded-full">Alpha</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>

				<div class="w-full md:w-1/3 xl:w-1/4 p-4">
					<div class="relative bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 ease-in-out">
						<div class="p-4">
							<h2 class="text-2xl font-bold">HTTP</h2>
							<p class="text-gray-600">HTTP server/client</p>
							<div class="flex justify-between items-center mt-4">
								<a href="https://cédille.org/paquets/HTTP"  class="bg-blue-500 text-white text-sm font-bold px-4 py-2 rounded-lg hover:bg-blue-600 transition-all duration-200">Documentation</a>
								<p class="text-gray-800 font-bold">v0.1</p> <!-- Version -->
							</div>
						</div>
						<div class="absolute mt-4 mr-4 top-0 right-0">
        					<span class="inline-block bg-red-800 text-white text-sm px-3 py-1 rounded-full">En développement</span> <!-- Étiquette d'état -->
    					</div>
					</div>
				</div>
            </div>
			<hr class="mt-8"/>
			<div class="w-full text-center">
				<a class="mt-8 mx-auto inline-block bg-gray-500 text-white text-sm px-5 py-2 rounded-full text-lg" href="//cédille.org">Voir les paquets communautaires</a>
			</div>
        </div>
	</div>

<?php
	}
];
