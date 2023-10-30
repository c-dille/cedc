<?php return [
	"title" => "Accueil",
	"render" => function() { ?>
<!-- Hero Section -->
<div class="pt-24">
	<div class="container px-3 mx-auto flex flex-wrap flex-col md:flex-row items-center">
		<div class="flex flex-col w-full md:w-2/5 justify-center items-start text-center md:text-left">
			<h1 class="my-4 text-5xl font-bold leading-tight">
				Cédille
			</h1>
			<div class="w-full" style="height: 12px;"></div>

			<p class="leading-normal text-2xl mb-8">
				<i>
					La cédille (de l'espagnol cedilla, « petit z ») est un diacritique de l'alphabet latin. Elle ne se place en français que sous la lettre c, autant sous une minuscule que sous une majuscule : ç, Ç.
				</i>
			</p>
			<!--button class="mx-auto lg:mx-0 hover:underline bg-gray-800 text-white font-bold rounded-full my-6 py-4 px-8 shadow-lg tilt">
				Commencer
			</button-->
		</div>
		<div class="w-full md:w-3/5 py-6 text-center">
			<img class="w-full md:w-4/5 z-50" src="/assets/cedilla.svg" alt="Cédille Hero Image" />
		</div>
	</div>
</div>

<!-- À propos du produit -->
<section id="about" class="flex flex-wrap py-12 m-12">
<div class="w-full" style="height: 40px;"></div>
	<div class="w-full md:w-1/2 order-2 md:order-1 pl-0 md:pl-12 mt-8 md:mt-0">
	<h2 class="text-3xl font-semibold">Flexibilité.</h2>
		<div class="w-full" style="height: 40px;"></div>
		<span class="text-lg mt-4">
			<p>Le système de macros hygiéniques au niveau AST permet de créer dynamiquement de nouvelles syntaxes dans votre code source sans le besoin de créer une extension externe pour un compilateur. Accélérez votre productivité tout en conservant une performance et une sécurité optimale. </p>
			<br/>
			<ul style="margin-left: 10px;" class="list-none md:list-disc text-lg mt-4">
				<li>Intéropabilité avec le CPP</li>
				<li>Évaluations lors de la compilation</li>
				<li>Liberté syntaxique absolue</li>
			</ul>
		</span>
	</div>
	<div class="w-full md:w-1/2 order-1 md:order-2 pr-0 md:pr-12">
		<pre class="prettyprint" style="border: 0px !important;">

		int	factorial(int x)
		{
			if !x
				return 1
			return n * factorial(n - 1)
		}

		ced_define macro fact(cedilla_context *ctx, ast_macro *l)
		{
			auto out = ast_match(l, EXPR, OP)
			if !strcmp(out.matches[1], "!")
			{
				return ast_edit(l, out.match_size,
					"factorial",
					"(",
					out.marches[0],
					")"
				)
			}
			return NEXT_MACRO
		}

		assert(3! == 3 * 2 * 1)
		assert(7! == factorial(7))
		assert(6! == factorial(ced_eval { print 6 }))
		ced_define { auto x = 5 }
		assert(ced_eval { print x }! == factorial(ced_eval { print x }))
		#define M2 x
		assert(M@ced_eval { print 2 } == ced_eval { x })
		assert(M2 == ced_eval { print M2 })
		</pre>
	</div>
</section>

<!-- Optimisation personnalisée -->
<section id="optimisation-personnalisee" class="flex flex-wrap py-12 m-12">
	<div class="w-full md:w-1/2 order-2 md:order-1 pl-0 md:pl-12 mt-8 md:mt-0">
		<pre class="prettyprint" style="border: 0px !important;">
		#include networking/server/tcp
		#include networking/server/http

		auto tcpServer = new TcpServer(8080)
		auto httpServer = new HttpServer(TcpServer)
		auto pgLink = new OdbcClient(pgsql, 127.0.0.1)

		httpServer.on('/bonjour', async lambda req, resp {
			resp.print "Bienvenue sur la cédille!"
		})

		httpServer.on('/login', async lambda req, resp {
			auto users = await pgLink.query {
				select * from user
				where email = resp.email and pw = hash(resp.pw)
			}
			if !users.length
				resp.print "Email or password incorect"
			else
				auth(resp, users[0])
		})

		httpServer.run()
		</pre>
	</div>
	<div class="w-full md:w-1/2 order-1 md:order-2 pr-0 md:pr-12">
		<h2 class="text-3xl font-semibold">Performance.</h2>
		<div class="w-full" style="height: 40px;"></div>
		<p class="text-lg mt-4">
		La gestion des opérations asynchrones en Rust/C++ est complexe et peut impacter les performances. En contraste, notre sur-ensemble du langage C propose une transformation des mots-clés async et await en callbacks et en fonctions en C standard, permettant ainsi une approche plus directe et potentiellement plus efficace.

		Grâce à l'intégration des fonctionnalités récentes du noyeau Linux tel que io_uring, notre super-ensemble facilite la gestion des tâches asynchrones, déverrouillant ainsi des performances optimales et un code plus lisible.
		<br/>
		<br/>
		Aussi nous utilisons un traitement des requêtes SQL par lot pour une exécution groupée sur le serveur, ce qui réduit considérablement le temps de latence réseau, en particulier dans des scénarios où de nombreuses petites opérations sont effectuées rapidement.
		En évitant un aller-retour client/serveur après chaque requête, nous optimisons les performances et le temps de réponse. Les applications peuvent ainsi gérer efficacement un grand nombre d'opérations SELECT, INSERT, UPDATE et DELETE en minimisant les délais d'attente et maximisant le débit des transactions.
		<br/>
		</p>
	</div>
</section>


<section id="about" class="flex flex-wrap py-12 m-12">
	<div class="w-full md:w-1/2 order-2 md:order-1 pl-0 md:pl-12 mt-8 md:mt-0">
		<h2 class="text-3xl font-semibold">Sécurité.</h2>
		<div class="w-full" style="height: 40px;"></div>
			<strong>Gestion de la mémoire</strong>
			<div class="w-full" style="height: 40px;"></div>
			<p>La mémoire est un aspect crucial dans la programmation, et sa gestion incorrecte peut conduire à des erreurs fatales. Notre super-ensemble du C facilite la gestion de la mémoire en automatisant la libération de la mémoire grâce à des références comptés à la compilation et en accompagnant le développeur dans sa gestion grâce à des erreurs de compilation, ce qui réduit significativement les risques de fuites de mémoire.</p>
			<br/>
			<p>Notre super-ensemble du C ajoute une couche de sûreté en prévenant les opérations non sécurisées comme la déréférenciation de pointeurs non valides, l'utilisation après la libération et l'utilisation après le déplacement.</p>
		</div>
	<div class="w-full md:w-1/2 order-1 md:order-2 pr-0 md:pr-12">
		<pre class="prettyprint" style="border: 0px !important;">
		void *ptr = malloc(42)
		defer scope { free(ptr) }
		// May also be parent_scope, program_scope.
		// Not defering immediatly after a defer
		// will result in a compile-time error.

		void *ptr2 = malloc(42)
		ptr = 0;
		// Will free ptr and forbid its usage without
		// a rewriting using compile-time refcount.

		int *ptr = 4;
		*(ptr) = 5;
		// Error : invalid address dereference
		</pre>
	</div>
</section>


<section id="optimisation-personnalisee" class="flex flex-wrap py-12 m-12">
	<div class="w-full md:w-1/2 order-2 md:order-1 pl-0 md:pl-12 mt-8 md:mt-0">
		<pre class="prettyprint" style="border: 0px !important;">
		int arr[5]
		for item in arr
			item = 0
		item[5] = 4
		// Error : array bound check

		int arr[...] = {0, 2, 5}
		// Dynamic array declaration

		arr[] = 4
		// Dynamic array pusing

		for item in arr
			arr[i] = arr[i + 1]
		// Error : array bound check
		</pre>
	</div>
	<div class="w-full md:w-1/2 order-1 md:order-2 pr-0 md:pr-12">
		<strong>Tableaux intéligents </strong>
		<div class="w-full" style="height: 40px;"></div>
		<span class="text-lg mt-4">
			<p>Les débordements de tableau sont des erreurs communes qui peuvent causer de nombreux effets indésirables. Notre super-ensemble du C effectue ces vérifications pendant la compilation pour que les accès aux tableaux restent dans les limites définies, contribuant ainsi à la robustesse du code.</p>
			<br/>
			<p>La possibilité de déclarer des tableaux de taille dynamique offre une flexibilité accrue pour la modélisation des données, tout en conservant la sûreté des types, la vérification des limites et en veillant à la délégation des comportements en cas d'erreur d'allocation.</p>
		</span>
	</div>
</section>




		<?php
	}
];

