<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->history
 * @param bool $this->disableComments
 */
?>
<div class="history">
	<h1>History</h1>
		<?php
			foreach ($this->history as $event) {
				$action = View::escape($event->getAction());
				if (userIsAllowed('people','view')) {
					$description = View::escape($event->getDescription());
					$description = $description ? $description : $action;
				}
				else {
					$description = $action;
				}
				echo "
				<div class=\"historyItem\">
				<h4>{$event->getActionDate(DATE_FORMAT)} $description</h4>
				</tr>
				";
					if (!$this->disableComments) {
						if ($event->getAction()=='categoryChange') {
							$j = json_decode($event->getNotes());
							if ($j) {
								$notes = "<table>";
								foreach ($j as $data) {
									$name = View::escape($data->name);
									$label = $data->label ? View::escape($data->label) : '';
									$value = is_array($data->value) ? implode(', ',$data->value) : $data->value;
									$value = View::escape($value);
									$notes.= "<tr><th>$name</th><td>$label</td><td>$value</td></tr>";
								}
								$notes.= "</table>";
							}
						}
						else {
							$notes = View::escape($event->getNotes());
						}
						echo "<p> $notes</p>";
					}
					
					echo "</div>";
			}
		?>
		</tbody>
	</table>
</div>
