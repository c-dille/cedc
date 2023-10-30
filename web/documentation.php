<?php return [
	"title" => "Documentation",
	"render" => function() { ?>
   <!-- Packages Section -->
    <div class="container mx-auto flex flex-wrap py-6" style="margin-top: 100px;">

        <!-- Page Title -->
        <h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
           Documentation
        </h1>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Création d'un projet
		</h2>

		<pre class="text-center w-full">$ mkdir test-app && cd test-app && ced init</pre>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Compilation
		</h2>
		<pre class="text-center w-full">$ cedc [options] [input files] [-o outfile]</pre>
		<br/>
		<br/>
		<table class="min-w-full bg-white rounded-lg overflow-hidden">
            <thead class="bg-gray-800 text-white">
                <tr>
                    <th class="w-1/3 py-2 px-4">Option</th>
                    <th class="w-2/3 py-2 px-4">Description</th>
                </tr>
            </thead>
            <tbody>
			<tr class="hover:bg-gray-100">
    			<td class="py-2 px-4">-c</td>
    			<td class="py-2 px-4">Compile and assemble, but do not link.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-o outfile</td>
				<td class="py-2 px-4">Specify output file name. By default, TCC outputs an executable named a.out.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-l[name]</td>
				<td class="py-2 px-4">Link with library 'name'.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Ldir</td>
				<td class="py-2 px-4">Add 'dir' to the list of directories to search for libraries.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Ipath</td>
				<td class="py-2 px-4">Add 'path' to the list of directories to search for header files.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Dsym[=val]</td>
				<td class="py-2 px-4">Define symbol 'sym' to 'val' (or 1 if 'val' is omitted).</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Usym</td>
				<td class="py-2 px-4">Undefine symbol 'sym'.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Wl,options</td>
				<td class="py-2 px-4">Pass linker options.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-Wp,options</td>
				<td class="py-2 px-4">Pass preprocessor options.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-E</td>
				<td class="py-2 px-4">Stop after the preprocessing stage; do not compile, assemble, or link.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-v</td>
				<td class="py-2 px-4">Display version information and exit.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-w</td>
				<td class="py-2 px-4">Suppress all warning messages.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-g</td>
				<td class="py-2 px-4">Generate debugging information.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-O[level]</td>
				<td class="py-2 px-4">Set optimization level. Currently, only -O0 (no optimization) is supported.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-std=c11</td>
				<td class="py-2 px-4">Specify C standard to adhere to (for example, c99 or C23).</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-bench</td>
				<td class="py-2 px-4">Benchmark the compilation time for files.</td>
			</tr>
			<tr class="hover:bg-gray-100">
				<td class="py-2 px-4">-run</td>
				<td class="py-2 px-4">Compile and run C source code directly.</td>
			</tr>

            </tbody>
        </table>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Ajout d'un paquet
		</h2>
		<pre class="text-center w-full">$ ced install [--global] [name]</pre>


		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Mise à jour des paquets
		</h2>
		<pre class="text-center w-full">$ ced install [--global]</pre>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Désinstallation d'un paquet
		</h2>

		<pre class="text-center w-full">$ ced uninstall [--global] [name]</pre>

		<h1 class="w-full my-2 text-5xl font-bold leading-tight text-center text-gray-800">
			___
		</h1>
		<h2 class="w-full my-2 text-4xl font-bold leading-tight text-center text-gray-600">
			Désinstallation
		</h2>

		<pre class="text-center w-full">$ ced uninstall </pre>
	</div>
		<?php
	}
];
