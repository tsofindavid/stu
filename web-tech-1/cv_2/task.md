Of course. Here is the translation of the assignment from Slovak to English:

***

**WEBTE1 Assignment No. 2 - Winter Semester 2025/2026**

**1. General Instructions**
*   All submitted pages must be valid. Check the validity of your created documents using a validator (HTML: https://validator.w3.org/, CSS3: https://jigsaw.w3.org/css-validator/. Modern IDEs have built-in validators that can be used).
*   Assignments should be optimized for the latest versions of Google Chrome and Firefox.
*   Assignments are always due by midnight on the day before the tutorial.
*   Late submission of an assignment is penalized by a point reduction (-2 points per week).
*   Submit assignments packaged in ZIP format. The name of the zipped file should be in the format `Zx_yyyyy`, where `x` denotes the assignment number and `yyyyy` is the student's surname in lowercase letters and without diacritics. Inside the zip, there should be a file named `index.html`, which is the file to be run first.
*   When submitting to MS Teams, attach a link to the location of your page on the school server as an attachment.
*   In case plagiarism is detected, consequences are to be expected.

**2. Exercise Assignment:**

Create a web page with a form for booking spaces and equipment for your sports event (alternatives are possible). In the form, allow the user to choose which room/court/space they are booking, at what time, and for what price. Furthermore, they will be able to choose which sports equipment they would like to borrow and for how many people. All this data will be stored in your code, i.e., it will not be drawn from any database or file. You can adapt the rest of the form's content, but the assignment must also meet the following requirements:

(1) The form must submit the following fields: first name, last name, gender, date of birth, and age. Check if the entered date of birth corresponds to the entered age (and vice versa). If these two pieces of data are not interconnected, ensure that the form cannot be submitted. The age should be automatically calculated based on the date of birth.

(2) The form will have at least 3 interconnected dropdown lists, i.e., the content of the second dropdown will depend on the selection in the first dropdown, and the content of the third dropdown will depend on the selection in the second dropdown.

(3) A part of the form will adapt based on which item the user selects in a switch (implemented via radio buttons). This means that a part of the form will either change, be revealed, or hidden, or at least one field will change (e.g., the form will have a "Payment by invoice" switch that will reveal additional form fields for invoice details).

(4) In one single-line text field, there must be an email address that contains the "@" symbol, at least 2 domains, where the top-level domain has 2-4 characters. There must be at least 3 characters before the "@" symbol.

(5) The form will also contain a checkbox field where the user will have the option to define their answer themselves. For example, the form might contain a question (I hope you think of something else) "What sport will you play?" with answers "football", "tennis", "handball". To the answers, it is necessary to add an option of the type "other, please specify". Upon selecting this alternative, a previously hidden text field will be displayed to the user, into which they can enter their answer.

(6) The form will contain at least one multi-line text field (textarea) and a hidden text field into which you will enter your name. This text field can be revealed by pressing a button.

(7) The form will contain a field - telephone number - and it will only be possible to enter a number in the international format. The field can also consist of two parts, where the first part is a dropdown list of prefixes to choose from, and into the second part, the number can be written.

(8) Several fields, at a minimum first name, last name, gender, date of birth, and age, will be mandatory fields of the form and must be visibly marked as required.

(9) For individual form fields, provide the user with a hint on how to fill out the given field. In case of incorrect input, the user must be informed immediately after leaving the field (i.e., not only upon form submission) what exactly the error is that prevents the form from being submitted (also in the case of interconnected fields).

(10) After pressing the form submission button, first provide the user with a preview of the services they have ordered, along with the final price. At the end of the preview, there will be a button to actually perform the final submission of the form. The preview must be generated dynamically, i.e., not by hiding and revealing elements. It must be possible to close the preview without submitting in order to subsequently adjust the form. Implement the solution as a layer over the page (modal).

(11) The page will be responsive, i.e., adapted to various screen sizes (desktop, tablet, mobile). For screen sizes of 768px and larger, the page will have at least two columns. For smaller displays, the columns will be placed under each other. Ensure the page displays correctly at any browser window size.

(12) Individual fields must be validated. In case of incorrect input, it is necessary to display a message for the user under each field (custom, not the native one created by `input type="submit"`) and highlight the field in color. You can perform the evaluation on each field separately or collectively when opening the preview. The preview must not open / the form must not be submitted if it contains invalid input.

(13) For all text and number fields, display the maximum allowed number of characters and the current number of characters entered (e.g., 13 / 20). Also, pay attention to the correct use of input types (input type - text, number, date, ...).

(14) It is necessary to disable automatic data completion (autofill) in the form.

The form must have an acceptable appearance (i.e., the individual items cannot just be "thrown in," but must be nicely formatted and aligned). The graphical impression is also evaluated. Graphical styling of all fields (input, textarea, radio, checkbox, ...) is expected so that they visually harmonize. The use of icons, custom fonts, and other graphic elements is welcome.

An example of the expected behavior can be seen in the image.

Use HTML, CSS, JS in the assignment. Do not use libraries and frameworks (e.g., Bootstrap).

**Submission of the assignment will consist of three points (all three will be part of the grading):**

(1) Fill out the created form (do not forget to fill in and mark all fields) and send it by email in one of the following ways:
    *   Using the `mailto` method.
    *   Using one of the freely available services on the Internet. For this purpose, you can use our service, which is currently available at: https://form2mail.iolab.sk/.
    In both cases, indicate your name in the message subject and address the form submission to the email address listed next to the name of the person evaluating your assignments:
    *   Matišák - feistu01@gmail.com
    *   Šefčík - feistu02@gmail.com
    *   Kocúr - feistu03@gmail.com

(2) Place the completed webpage with the form into MS Teams, Assignment 2.

(3) Place the functional website on the school server available to you.
