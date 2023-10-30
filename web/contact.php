<?php return [
	"title" => "Prix",
	"render" => function() { ?>
    <div class="relative container mx-auto py-6" style="margin-top: 100px; ">
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			Contact
        </h1>
		<br/>
		<br/>
		<div class="bg-white p-6 rounded-lg shadow-lg">
            <h1 class="text-2xl font-bold mb-6">Formulaire de contact</h1>

            <form action="/path-to-your-server-side-handler" method="POST">
                <div class="mb-4">
                    <label class="block text-gray-700 text-sm font-bold mb-2" for="name">Nom</label>
                    <input class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline" id="name" type="text" placeholder="Votre nom" name="name" required>
                </div>

                <div class="mb-4">
                    <label class="block text-gray-700 text-sm font-bold mb-2" for="email">Email</label>
                    <input class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline" id="email" type="email" placeholder="exemple@domaine.com" name="email" required>
                </div>

				<div class="mb-4">
					<label class="block text-gray-700 text-sm font-bold mb-2" for="contact-type">Objet</label>
					<div class="relative">
						<select class="block appearance-none w-full bg-white border border-gray-400 hover:border-gray-500 px-4 py-2 pr-8 rounded shadow leading-tight focus:outline-none focus:shadow-outline" id="contact-type" name="contactType">
							<option value="technical">Problème technique</option>
							<option value="commercial">Commercial / Demande de devis</option>
							<option value="partnership">Partenariat</option>
							<!-- Vous pouvez ajouter d'autres options si nécessaire -->
						</select>
						<div class="pointer-events-none absolute inset-y-0 right-0 flex items-center px-2 text-gray-700">
							<svg class="fill-current h-4 w-4" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20"><path d="M9.293 12.95l.707.707L15.657 8l-1.414-1.414L10 10.828 5.757 6.586 4.343 8z"/></svg>
						</div>
					</div>
				</div>


                <div class="mb-6">
                    <label class="block text-gray-700 text-sm font-bold mb-2" for="message">Message</label>
                    <textarea class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline" id="message" rows="4" placeholder="Entrez votre message ici..." name="message" required></textarea>
                </div>

                <div class="flex items-center justify-between">
                    <button class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline" type="submit">Envoyer</button>
                </div>
            </form>
        </div>
	</div>

<?php }
];
